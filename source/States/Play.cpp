#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Play.hpp"
#include "Tools/Debug.hpp"


Play::Play(GameData& gameData, const SettingsData& settingsData) :
    m_gameData(gameData),
    m_conductor(gameData.songData.music),
    m_settingsData(settingsData)
{
    m_activeScreens.reserve(m_gameData.screens.size());
}

void Play::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) 
        {
        case sf::Keyboard::Space:
            if (m_conductor.GetStatus() != sf::SoundSource::Playing) 
            {
                m_conductor.Play();
            }
            else 
            {
                m_conductor.Pause();
            }
            break;
        case sf::Keyboard::S:
            m_conductor.Stop();
            break;
        case::sf::Keyboard::Escape:
            m_exit = true;
            break;
        case sf::Keyboard::Right:
            m_conductor.Move(5.f);
            break;
        case sf::Keyboard::Left:
            m_conductor.Move(-5.f);
            break;
        }
    }

    // if (event.type == sf::Event::MouseWheelScrolled) {
    //     float delta = event.mouseWheelScroll.delta * 0.1f;
    //     if (0.2f < m_camera.zoom + delta && m_camera.zoom + delta < 5.f) {
    //         m_camera.zoom += delta;
    //     }
    // }
}

State::Type Play::Update(const sf::Time& dt) 
{
    if (m_exit) 
    {
        m_gameData.Clear();
        return State::Type::Menu;
    }

    if (m_conductor.GetStatus() == sf::SoundSource::Playing)
    {
        m_timer += dt.asSeconds();
        m_conductor.Normalize(m_timer);
    }
    
    for (auto& screen: m_gameData.screens)
    {
        if (m_timer >= screen.beginTime && m_timer <= screen.endTime && !screen.used)
        {  
            addScreen(&screen);
        }
        if (m_timer > screen.endTime && screen.used)
        {
            //removeScreen(screen.id);
        }
    }

    int cnt = 1;
    for (auto screen: m_activeScreens)
    {   
        Platform& curPlatform = screen->map.GetNextPlatform(m_timer);
        if (!screen->map.isEnd())
        {
            screen->square.Update(m_timer, curPlatform);
        }
        screen->camera.Update(dt);
        cnt++;
    }
    return State::Type::None;
}

void Play::Render(sf::RenderWindow& window) 
{
    //drawBackground(window);
    for (auto screen: m_activeScreens)
    {   
        screen->camera.SetView();
        screen->map.Render(window, screen->camera);
        screen->square.Render(window);
    }
}

void Play::drawBackground(sf::RenderWindow& window)
{
    sf::RectangleShape rect({5000.f, 5000.f});
    rect.setOrigin({2500.f, 2500.f});
    rect.setPosition({0.f, 100000.f});
    rect.setFillColor(sf::Color::Black);
    
    sf::View view = window.getDefaultView();
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.0f));
    view.setCenter(0.f, 100000.f);

    //window.setView(view);
    window.draw(rect);
}

void Play::addViewport(int id)
{
    Viewport next; next.id = id;
    if (m_viewports.empty())
    {
        next.rect = {0.f, 0.f, 1.f, 1.f};
        m_viewports.emplace_back(next);
        return;
    }

    Viewport prev = m_viewports.front();
    m_viewports.pop_front();
    
    float indent = 0.005f;
    sf::FloatRect nextRect, prevRect;
    nextRect = prevRect = prev.rect;
    if (prev.rect.width * m_settingsData.windowSize.x >= prev.rect.height * m_settingsData.windowSize.y)
    {   
        prevRect.width /= 2.f;
        prevRect.width -= indent / 2.f;

        nextRect.width /= 2.f;
        nextRect.width -= indent / 2.f;
        nextRect.left = prevRect.left + prevRect.width + indent;
    }
    else
    {
        prevRect.height /= 2.f;
        prevRect.height -= indent / 2.f;

        nextRect.height /= 2.f;
        nextRect.height -= indent / 2.f;
        nextRect.top = prevRect.top + prevRect.height + indent;
    }

    prev.rect = prevRect;
    next.rect = nextRect;

    m_viewports.emplace_back(prev);
    m_viewports.emplace_back(next);

    for (auto& viewport: m_viewports)
    {
        m_gameData.screens[viewport.id].camera.SetViewport(viewport.rect);
    }
}

void Play::addScreen(GameData::Screen* screen)
{
    addViewport(screen->id);
    const sf::Vector2f* squarePos = m_gameData.screens[screen->id].square.GetPositionRef(); 
    screen->camera.Init(m_gameData.windowPt, getViewportByID(screen->id), squarePos, *squarePos, sf::Vector2f(m_settingsData.windowSize));
    screen->used = true;
    m_activeScreens.emplace_back(screen);
}

sf::FloatRect& Play::getViewportByID(int id)
{
    for (auto& viewport: m_viewports)
    {
        if (viewport.id == id)
        {
            return viewport.rect;
        }
    }
}

void Play::removeScreen(int id)
{
    for (int i = 0; i < m_activeScreens.size(); ++i)
    {
        if (m_activeScreens[i]->id == id)
        {
            m_activeScreens.erase(m_activeScreens.begin() + i);
            break;
        }
    }
    m_gameData.screens[id].used = false;
    removeViewport(id);
}

// not working properly
void Play::removeViewport(int id)
{   
    if (m_viewports.size() < 2)
    {
        return;
    }

    int pos;
    for (auto it = m_viewports.begin(); it != m_viewports.end(); ++it)
    {
        if (it->id == id)
        {
            pos = it - m_viewports.begin();
            break;
        }
    }

    int next = (pos == m_viewports.size() - 1 ? pos - 1 : pos + 1);
    if (pos > next)
    {
        std::swap(next, pos);
    }
    Viewport left = m_viewports[pos];
    Viewport right = m_viewports[next];
    m_viewports.erase(m_viewports.begin() + pos);
    m_viewports.erase(m_viewports.begin() + pos);

    Viewport vp; vp.id = (id == left.id ? right.id : left.id);
    if (left.rect.height == right.rect.height && left.rect.width == right.rect.width)
    {
        if (left.rect.width * m_settingsData.windowSize.x >= left.rect.height * m_settingsData.windowSize.y)
        {
            sf::FloatRect rect;
            rect.top = std::min(left.rect.top, right.rect.top);
            rect.left = std::min(left.rect.left, right.rect.top);
            rect.height = left.rect.height + right.rect.height;
            rect.width = left.rect.width;

            vp.rect = rect;
        }
        else
        {
            sf::FloatRect rect;
            rect.top = std::min(left.rect.top, right.rect.top);
            rect.left = std::min(left.rect.left, right.rect.top);
            rect.height = left.rect.height;
            rect.width = left.rect.width + right.rect.width;

            vp.rect = rect;
        }
    }

    m_viewports.insert(m_viewports.begin() + pos, vp);
    for (auto& viewport: m_viewports)
    {
        m_gameData.screens[viewport.id].camera.SetViewport(viewport.rect);
    }
}

