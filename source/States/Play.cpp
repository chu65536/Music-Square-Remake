#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Play.hpp"
#include "Tools/Debug.hpp"


Play::Play(GameData& gameData, const SettingsData& settingsData) :
    m_gameData(gameData),
    m_conductor(gameData.songData.music),
    m_settingsData(settingsData)
{
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
        if (screen.Activate(m_timer))
        {   
            m_activeScreens.emplace_back(&screen);
            updateViewports();
        }
        if (screen.Idle(m_timer))
        {
            removeScreen(screen.GetID());
            updateViewports();
        }
    }
    for (auto screen: m_activeScreens)
    {   
        screen->Update(dt, m_timer);
    }   
    return State::Type::None;
}

void Play::updateViewports()
{
    std::deque<sf::FloatRect> dq;
    int n = m_activeScreens.size();
    for (int i = 0; i < n; ++i)
    {
        addViewport(dq);
    }

    for (int i = 0; i < n; ++i)
    {
        m_activeScreens[i]->SetViewport(dq[i]);
    }
}   

void Play::addViewport(std::deque<sf::FloatRect>& dq)
{
    if (dq.empty())
    {
        dq.emplace_back(0.f, 0.f, 1.f, 1.f);
        return;
    }

    sf::FloatRect prev = dq.front();
    dq.pop_front();
    sf::FloatRect next = prev;
    float indent = 0.005f;
    if (prev.width * m_settingsData.windowSize.x >= prev.height * m_settingsData.windowSize.y)
    {
        prev.width = (prev.width - indent) * 0.5f;

        next.width = (next.width - indent) * 0.5f;
        next.left = prev.left + prev.width + indent;
    }
    else
    {
        prev.height = (prev.height - indent) * 0.5f;

        next.height = (next.height - indent) * 0.5f;
        next.top = prev.top + prev.height + indent;
    }

    dq.push_back(prev);
    dq.push_back(next);
}

void Play::removeScreen(int id)
{
    if (m_activeScreens.size() < 2) 
    {
        return;
    }
    
    int localId;
    for (int i = 0; i < m_activeScreens.size(); ++i)
    {
        if (m_activeScreens[i]->GetID() == id)
        {
            localId = i;
            break;
        }
    }
    m_activeScreens.erase(m_activeScreens.begin() + localId);
}

void Play::Render(sf::RenderWindow& window) 
{
    for (auto screen: m_activeScreens)
    {       
        screen->Render(window);
    }
}

