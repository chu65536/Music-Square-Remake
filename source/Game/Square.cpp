#include <iostream>
#include "Game/Square.hpp"
#include "Tools/Math.hpp"


void Square::Init(const SettingsData& settingsData, const sf::Vector2f& startPoint) 
{
    m_speed_ = settingsData.squareSpeed;
    m_position = startPoint;
    m_rect = sf::RectangleShape(settingsData.squareSize);
    m_rect.setOrigin(settingsData.squareSize / 2.f);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(settingsData.squareColor);
    m_rect.setOutlineThickness(settingsData.squareOutlineThickness);
    m_rect.setOutlineColor(settingsData.squareOutlineColor);
    m_bounds = Math::GetBounds(m_rect);
}

void Square::Update(float time, Platform& platform) 
{
    m_position = platform.GetPosition();
    float deltaTime = time - platform.GetTime();
    if (deltaTime < 0.f) return;
    Platform::Direction dir = platform.GetDirection();
    m_speed_ = platform.GetSpeedAfter();
    switch(dir) 
    {
    case Platform::Direction::Up:
        m_speed_.y *= (m_speed_.y < 0 ? -1 : 1);
        break;
    case Platform::Direction::Left:
        m_speed_.x *= (m_speed_.x < 0 ? -1 : 1);
        break;
    case Platform::Direction::Down:
        m_speed_.y *= (m_speed_.y < 0 ? 1 : -1);
        break;
    case Platform::Direction::Right:
        m_speed_.x *= (m_speed_.x < 0 ? 1 : -1);
        break;
    }
    m_position += m_speed_ * deltaTime;
    m_rect.setPosition(m_position);
}

void Square::Render(sf::RenderWindow& window) {
    window.draw(m_rect);
}

void Square::SetSpeed(const sf::Vector2f& speed) {
    m_speed_ = speed;
}

const sf::Vector2f* Square::GetPositionRef() const 
{
    return &m_position;
}

