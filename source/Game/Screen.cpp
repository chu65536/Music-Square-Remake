#include "Game/Screen.hpp"

Screen::Screen(int id, Square&& square, Map&& map, Camera&& camera):
    m_id(id), m_square(std::move(square)), m_map(std::move(map)), m_camera(std::move(camera))
{
}

void Screen::Update(const sf::Time& dt, float time)
{
    Platform& curPlatform = m_map.GetNextPlatform(time);
    m_square.Update(time, curPlatform);
    m_camera.Update(dt, m_square.GetPosition());
}

void Screen::Render(sf::RenderWindow& window)
{   
    m_camera.SetViewport(m_viewport);
    m_camera.SetView(window);
    m_map.Render(window, m_camera);
    m_square.Render(window);
    drawName(window);
}

void Screen::CalcActiveTime(const std::vector<float>& delays)
{
    float begin = delays[0];

    float wait = 5.f;
    float delay = 1.0f;
    for (int i = 1; i < delays.size(); ++i)
    {
        if (delays[i] - delays[i - 1] > wait)
        {
            m_activeTime.emplace_back(begin - delay, delays[i - 1] + delay);
            begin = delays[i];
        }
    }
    m_activeTime.emplace_back(begin, delays[delays.size() - 1]);
}

bool Screen::Activate(float time)
{   
    if (m_active)
    {
        return false;
    }

    for (auto& [x, y]: m_activeTime)
    {
        if (x <= time && time <= y)
        {      
            m_camera.SetPosition(m_square.GetPosition());
            m_active = true;
            return true;
        }
    }

    return false;
}

bool Screen::Idle(float time)
{
    if (!m_active)
    {
        return false;
    }

    for (auto& [x, y]: m_activeTime)
    {
        if (x <= time && time <= y)
        {
            return false;
        }
    }

    m_active = false;
    return true;
}

int Screen::GetID() const
{
    return m_id;
}

std::string Screen::GetName() const
{
    return m_name;
}

void Screen::drawName(sf::RenderWindow& window)
{
    sf::Text text;
    text.setFont(m_font);
    text.setString(m_name);
    text.setCharacterSize(40);
    text.setFillColor(m_square.GetColor());

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width * 0.5f, textRect.top  + textRect.height * 0.5f);
    sf::Vector2f pos = m_camera.GetPosition();
    pos.y += (float)window.getSize().y * m_viewport.height * 0.5f - textRect.height;
    text.setPosition(pos);
    text.setOutlineThickness(3.f);
    window.draw(text);
}

void Screen::SetViewport(const sf::FloatRect& viewport)
{
    m_viewport = viewport;
}

void Screen::SetName(const std::string& name)
{
    m_name = name;
}

void Screen::SetFont(const std::string& path)
{
    if (!m_font.loadFromFile(path))
    {
        std::cerr << "Error: font is not found" << std::endl;
    }
}

