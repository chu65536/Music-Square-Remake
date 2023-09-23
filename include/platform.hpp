#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "configdata.hpp"


class Platform {
public:
    enum class Direction { Down, Left, Up, Right };
    Platform(
        sf::Vector2f position,
        std::vector<Platform::Direction> dirs, 
        double time, 
        sf::Vector2f speedBefore,
        const ConfigData& data
    );

    sf::Vector2f GetPosition() const;
    const sf::RectangleShape& GetRect() const;
    float GetTime() const;
    Platform::Direction GetDirection() const;
    sf::Vector2f GetSpeedBefore() const;
    sf::Vector2f GetSpeedAfter() const;
    void AdaptSpeedAfter(sf::Vector2f speed);
    bool TryAnotherDir();
private:
    void setDirection();
    void setSpeedAfter();
    const ConfigData& data_;
    const sf::Vector2f position_;
    sf::Vector2f size_;
    Platform::Direction direction_;
    const double time_;
    sf::RectangleShape rect_;
    sf::Vector2f speedBefore_;
    sf::Vector2f speedAfter_;
    std::vector<Platform::Direction> possibleDirections_;
};