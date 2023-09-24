#include <iostream>
#include "Game/Square.hpp"
#include "Adds/Math.hpp"

void Square::Init(const UserData& data) {
    m_position = data.position;
    m_speed_ = data.speed;
    m_rect = sf::RectangleShape(data.squareSize);
    m_rect.setOrigin(data.squareSize.x / 2, data.squareSize.y / 2);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(data.squareColor);
    m_rect.setOutlineThickness(-data.squareOutlineThickness);
    m_rect.setOutlineColor(data.squareOutlineColor);
    m_bounds = Math::GetBounds(m_rect);
}

void Square::Update(float time, const Platform& platform) {
    m_position = platform.GetPosition();
    float deltaTime = time - platform.GetTime();
    Platform::Direction dir = platform.GetDirection();
    m_speed_ = platform.GetSpeedAfter();
    switch(dir) {
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

const sf::Vector2f& Square::GetPositionRef() const {
    return m_position;
}
