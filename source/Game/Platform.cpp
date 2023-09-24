#include <algorithm>
#include "Game/Platform.hpp"
#include "Adds/Math.hpp"


Platform::Platform(
    const sf::Vector2f& position,
    std::vector<Platform::Direction> dirs,
    double time,
    const sf::Vector2f& speedBefore,
    const UserData& data
)   :
    m_position(position),
    m_possibleDirections(dirs),
    m_time(time),
    m_speedBefore(speedBefore),
    m_data(data),
    m_size(data.platformSize)
{
    m_rect.setPosition(m_position);    
    m_rect.setFillColor(data.platformColor);

    setDirection();
}

void Platform::setDirection() {
    if (m_possibleDirections.size() == 0) {
        return;
    }

    m_direction = m_possibleDirections[rand() % m_possibleDirections.size()];
    m_possibleDirections.erase(std::remove(m_possibleDirections.begin(), m_possibleDirections.end(), m_direction), m_possibleDirections.end());
    switch(m_direction) {
    case Platform::Direction::Down:
        m_size = sf::Vector2f(m_data.squareSize.x, m_data.platformSize.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.y / 2);
        m_rect.setRotation(0.f);
        break;
    case Platform::Direction::Left:
        m_size = sf::Vector2f(m_data.squareSize.y, m_data.platformSize.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.x / 2);
        m_rect.setRotation(90.f);
        break;
    case Platform::Direction::Up:
        m_size = sf::Vector2f(m_data.squareSize.x, m_data.platformSize.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.y / 2);
        m_rect.setRotation(180.f);
        break;
    case Platform::Direction::Right: 
        m_size = sf::Vector2f(m_data.squareSize.y, m_data.platformSize.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.x / 2);
        m_rect.setRotation(270.f);
        break;
    }

    setSpeedAfter();
    m_bounds = Math::GetBounds(m_rect);
}

void Platform::setSpeedAfter() {
    m_speedAfter = m_speedBefore;
    if (m_direction == Platform::Direction::Up || m_direction == Platform::Direction::Down) {
        m_speedAfter.y *= -1;
    }
    if (m_direction == Platform::Direction::Left || m_direction == Platform::Direction::Right) {
        m_speedAfter.x *= -1;
    }
}

void Platform::AdaptSpeedAfter(const sf::Vector2f& speed) {
    float kx = (m_speedAfter.x > 0 ? 1 : -1);
    float ky = (m_speedAfter.y > 0 ? 1 : -1);
    m_speedAfter = speed;
    m_speedAfter.x *= kx;
    m_speedAfter.y *= ky;
}

bool Platform::TryAnotherDirection() {
    if (m_possibleDirections.size() == 0) {
        return false;
    }
    setDirection();
    return true;
}

sf::Vector2f Platform::GetPosition() const {
    return m_position;
}

const sf::RectangleShape& Platform::GetRect() const {
    return m_rect;
}

float Platform::GetTime() const {
    return m_time;
}

Platform::Direction Platform::GetDirection() const {
    return m_direction;
}

sf::Vector2f Platform::GetSpeedBefore() const {
    return m_speedBefore;
}

sf::Vector2f Platform::GetSpeedAfter() const {
    return m_speedAfter;
}

const std::vector<sf::Vector2f>& Platform::GetBounds() const {
    return m_bounds;
}