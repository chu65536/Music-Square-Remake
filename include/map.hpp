#pragma once

#include <SFML/Graphics.hpp>


class Platform {
public:
    enum class Direction { Down, Left, Up, Right };
    Platform(sf::Vector2f position, Platform::Direction direction, double time);
    sf::RectangleShape GetRect() const;
private:
    const sf::Vector2f position_;
    const Platform::Direction direction_;
    const double time_;
    sf::RectangleShape rect_;
};

class Map {
public:
    Map() = default;
    void Render(sf::RenderWindow& window) const;
    void Generate(const std::vector<double>& delays);
private:
    std::vector<Platform> platforms_;
};