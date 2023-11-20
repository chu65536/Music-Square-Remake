#include <iostream>
#include "Game/Square.hpp"
#include "Tools/Math.hpp"


Square::Square(const SettingsData& settingsData, const sf::Vector2f& startPoint) :
    m_position(startPoint),
    m_speed(settingsData.squareSpeed), 
    m_rect(settingsData.squareSize)

{
    m_color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    m_rect.setOrigin(settingsData.squareSize / 2.f);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(m_color);
    m_rect.setOutlineThickness(settingsData.squareOutlineThickness);
    m_rect.setOutlineColor(settingsData.squareOutlineColor);
}

void Square::Update(float time, Platform& platform) 
{   
    m_position = platform.GetPosition();
    float deltaTime = time - platform.GetTime();
    if (deltaTime < 0.f) return;
    Platform::Direction dir = platform.GetDirection();
    m_speed = platform.GetSpeedAfter();
    switch(dir) 
    {
    case Platform::Direction::Up:
        m_speed.y *= (m_speed.y < 0 ? -1 : 1);
        break;
    case Platform::Direction::Left:
        m_speed.x *= (m_speed.x < 0 ? -1 : 1);
        break;
    case Platform::Direction::Down:
        m_speed.y *= (m_speed.y < 0 ? 1 : -1);
        break;
    case Platform::Direction::Right:
        m_speed.x *= (m_speed.x < 0 ? 1 : -1);
        break;
    }
    m_position += m_speed * deltaTime;
    m_rect.setPosition(m_position);
}

void Square::Render(sf::RenderWindow& window) 
{
    window.draw(m_rect);
}

void Square::SetSpeed(const sf::Vector2f& speed) 
{
    m_speed = speed;
}

sf::Vector2f Square::GetPosition() const
{
    return m_position;
}

sf::Color Square::GetColor() const
{
    return m_color;
}


