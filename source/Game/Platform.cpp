#include <iostream>
#include <algorithm>
#include "Game/Platform.hpp"
#include "Tools/Math.hpp"
#include <fstream>


Platform::Platform(Data&& data): 
    m_data(data),
    m_position(data.position),
    m_time(data.time),
    m_possibleDirections(data.directions),
    m_color(data.color),
    m_outlineColor(data.outlineColor),
    m_outlineThickness(data.outlineThickness),
    m_speedBefore(data.speedBefore),
    m_speedAfter(data.speedAfter)
{
    m_rect.setPosition(m_position);  
    m_rect.setFillColor(m_color);
    m_rect.setOutlineColor(m_outlineColor);
    m_rect.setOutlineThickness(m_outlineThickness);

    setDirection();
}

void Platform::setDirection() 
{
    if (m_possibleDirections.size() == 0) 
    {
        return;
    }

    m_direction = m_possibleDirections[rand() % m_possibleDirections.size()];
    m_possibleDirections.erase(std::remove(m_possibleDirections.begin(), m_possibleDirections.end(), m_direction), m_possibleDirections.end());
    rotate();
    updateSpeedAfter();
}

void Platform::updateSpeedAfter() {
    float kx = (m_speedBefore.x > 0 ? 1 : -1);
    float ky = (m_speedBefore.y > 0 ? 1 : -1);
    if (m_direction == Platform::Direction::Up || m_direction == Platform::Direction::Down) 
    {
        ky *= -1;
    }
    if (m_direction == Platform::Direction::Left || m_direction == Platform::Direction::Right) 
    {
        kx *= -1;
    }
    m_speedAfter.x = abs(m_speedAfter.x) * kx;
    m_speedAfter.y = abs(m_speedAfter.y) * ky;
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

void Platform::Render(sf::RenderWindow& window) 
{
    window.draw(m_rect);
}

sf::Vector2f Platform::GetPosition() const 
{
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

void Platform::Export(std::ofstream& file)
{
    file << m_position.x << ' ' << m_position.y << ' ';
    file << m_size.x << ' ' << m_size.y << ' ';
    file << static_cast<int>(m_direction) << ' ';
    file << m_time << ' ';
    file << (int)m_color.r << ' ' << (int)m_color.g << ' ' << (int)m_color.b << ' ';
    file << m_outlineThickness << ' ';
    file << (int)m_outlineColor.r << ' ' << (int)m_outlineColor.g << ' ' << (int)m_outlineColor.b << ' ';
    file << m_speedBefore.x << ' ' << m_speedBefore.y << ' ';
    file << m_speedAfter.x << ' ' << m_speedAfter.y << ' ';
    file << '\n';
}