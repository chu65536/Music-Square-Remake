#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <mutex>
#include <unordered_map>
#include "platform.hpp"
#include "configdata.hpp"
#include "square.hpp"


class Map {
public:
    void Render(sf::RenderWindow& window) const;
    void Init(const std::vector<double>& delays, const ConfigData* configData, Square* square, std::mutex& m);
    void Clear();
    const std::vector<Platform>& GetPlatforms() const;
    const Platform& GetNextPlatform(float time);
    void addBackground();
    bool isEnd() const;
    size_t GetSize() const;
    const sf::Vector2f& GetPositionRef() const;
    bool IsFailed() const;
private:
    void makePlatforms(const std::vector<double>& delays, std::mutex& m);
    void makeFirstPlatform();
    Platform makeNextPlatform(const sf::Vector2f& position, double time, const sf::Vector2f& speed);
    bool checkCollisions(const Platform& platform);
    std::vector<Platform::Direction> getPossibleDirs(const sf::Vector2f speed) const;
    void revert(std::unordered_map<int, int>& attempts, size_t& size);
    sf::Vector2f getAdaptedSpeed(float dt) const;

    const ConfigData* configDataPt_ = nullptr;
    Square* squarePt_ = nullptr;
    size_t curPlatform = 0;
    std::vector<Platform> platforms_;
    std::vector<sf::RectangleShape> background_;
    sf::Vector2f centerPoint_;
    bool failed_ = false;
};