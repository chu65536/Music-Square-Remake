#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "configdata.hpp"


class Platform {
public:
    enum class Direction { Down, Left, Up, Right };
    Platform(sf::Vector2f position, std::vector<Platform::Direction> dirs, double time, const ConfigData* data);
    sf::Vector2f GetPosition() const;
    sf::RectangleShape GetRect() const;
    float GetTime() const;
    Platform::Direction GetDirection() const;
    bool TryAnotherDir();
private:
    void setDirection();
    const sf::Vector2f position_;
    Platform::Direction direction_;
    const double time_;
    sf::RectangleShape rect_;
    std::vector<Platform::Direction> possibleDirections_;
};