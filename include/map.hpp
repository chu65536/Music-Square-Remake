#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "platform.hpp"
#include "configdata.hpp"
#include "square.hpp"


class Map {
public:
    void Render(sf::RenderWindow& window) const;
    void Init(const std::vector<double>& delays, const ConfigData* configData, Square* square);
    void Clear();
    const Platform& GetNextPlatform(float time);
    bool isEnd() const;
private:
    void makePlatforms(const std::vector<double>& delays);
    void makeFirstPlatform(sf::Vector2f& speed);
    Platform makeNextPlatform(const sf::Vector2f& position, double time, const sf::Vector2f& speed);
    void updateDirection(sf::Vector2f& speed, Platform::Direction dir);
    bool checkCollisions(const Platform& platform);
    std::vector<Platform> platforms_;
    const ConfigData* configDataPt_ = nullptr;
    Square* squarePt_ = nullptr;
    size_t curPlatform = 0;
};