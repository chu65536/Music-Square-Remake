#include <iostream>
#include <algorithm>
#include "Game/Platform.hpp"
#include "Tools/Math.hpp"


Platform::Platform(Data&& data): 
    m_data(data),
    m_position(data.position),
    m_time(data.time),
    m_possibleDirections(data.directions),
    m_color(data.color),
    m_speedBefore(data.speedBefore),
    m_active(false)
{
    m_rect.setPosition(m_position); 
    float k = 0.f;
    sf::Color col = data.color;
    col.r *= k; col.g *= k; col.b *= k;   
    m_rect.setFillColor(col);

    setDirection();
}

void Platform::setDirection() {
    if (m_possibleDirections.size() == 0) {
        return;
    }

    m_direction = m_possibleDirections[rand() % m_possibleDirections.size()];
    m_possibleDirections.erase(std::remove(m_possibleDirections.begin(), m_possibleDirections.end(), m_direction), m_possibleDirections.end());
    rotate();
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

void Platform::Render(sf::RenderWindow& window) {
    window.draw(m_rect);
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

void Platform::AddCandleBounds(candle::EdgeVector& pool) const{
    for (size_t i = 1; i < m_bounds.size(); ++i) {
        pool.emplace_back(m_bounds[i - 1], m_bounds[i]);
    }
    pool.emplace_back(m_bounds[m_bounds.size() - 1], m_bounds[0]);
}

void Platform::MakeActive() {
    if (m_active) return;

    m_active = true;
    m_rect.setFillColor(m_color);
}

void Platform::rotate() {
    switch(m_direction) {
    case Platform::Direction::Down:
        m_size = sf::Vector2f(std::max(m_data.squareSize.x, m_data.size.x), m_data.size.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.y / 2);
        m_rect.setRotation(0.f);
        break;
    case Platform::Direction::Left:
        m_size = sf::Vector2f(std::max(m_data.squareSize.y, m_data.size.x), m_data.size.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.x / 2);
        m_rect.setRotation(90.f);
        break;
    case Platform::Direction::Up:
        m_size = sf::Vector2f(std::max(m_data.squareSize.x, m_data.size.x), m_data.size.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.y / 2);
        m_rect.setRotation(180.f);
        break;
    case Platform::Direction::Right: 
        m_size = sf::Vector2f(std::max(m_data.squareSize.y, m_data.size.x), m_data.size.y);
        m_rect.setSize(m_size);
        m_rect.setOrigin(m_size.x / 2, -m_data.squareSize.x / 2);
        m_rect.setRotation(270.f);
        break;
    }
}