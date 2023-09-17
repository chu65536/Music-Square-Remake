#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "configdata.hpp"


class Platform {
public:
    enum class Direction { Down, Left, Up, Right };
    Platform(sf::Vector2f position, Platform::Direction direction, double time, const ConfigData& data);
    sf::Vector2f GetPosition() const;
    sf::RectangleShape GetRect() const;
    float GetTime() const;
    Platform::Direction GetDirection() const;
private:
    const sf::Vector2f position_;
    const Platform::Direction direction_;
    const double time_;
    sf::RectangleShape rect_;
};

class Map {
public:
    void Render(sf::RenderWindow& window) const;
    void Generate(const std::vector<double>& delays, const ConfigData& configData);
    void Clear();
    const Platform& GetNextPlatform(float time);
    bool isEnd() const;
private:
    void makePlatforms(const std::vector<double>& delays);
    std::vector<Platform> platforms_;
    const ConfigData* configDataPt_ = nullptr;
    size_t curPlatform = 0;
};