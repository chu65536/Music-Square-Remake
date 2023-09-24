#pragma once

#include <SFML/Graphics.hpp>
#include <Candle/RadialLight.hpp>
#include <vector>
#include "Data/UserData.hpp"


class Platform {
public:
    enum class Direction { Down, Left, Up, Right };
    Platform(
        const sf::Vector2f& position,
        std::vector<Platform::Direction> dirs, 
        double time, 
        const sf::Vector2f& speedBefore,
        const UserData& data
    );

    sf::Vector2f GetPosition() const;
    const sf::RectangleShape& GetRect() const;
    float GetTime() const;
    Platform::Direction GetDirection() const;
    sf::Vector2f GetSpeedBefore() const;
    sf::Vector2f GetSpeedAfter() const;
    void AdaptSpeedAfter(const sf::Vector2f& speed);
    bool TryAnotherDirection();
    const std::vector<sf::Vector2f>& GetBounds() const;
private:
    void setDirection();
    void setSpeedAfter();

    const UserData& m_data;
    const sf::Vector2f m_position;
    const double m_time;
    sf::Vector2f m_size;
    Platform::Direction m_direction;
    sf::RectangleShape m_rect;
    const sf::Vector2f m_speedBefore;
    sf::Vector2f m_speedAfter;
    std::vector<Platform::Direction> m_possibleDirections;
    candle::RadialLight m_lightSource;
    std::vector<sf::Vector2f> m_bounds;
};