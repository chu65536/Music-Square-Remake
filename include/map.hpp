#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <mutex>
#include <map>
#include "platform.hpp"
#include "configdata.hpp"
#include "square.hpp"
#include "camera.hpp"


class Map {
public:
    void Render(sf::RenderWindow& window, const Camera& cam);
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
    void makeGridMap();

    const ConfigData* configDataPt_ = nullptr;
    Square* squarePt_ = nullptr;
    size_t curPlatform = 0;
    std::vector<Platform> platforms_;
    std::vector<sf::RectangleShape> background_;
    std::vector<sf::RectangleShape> backgroundCover_;
    sf::Vector2f centerPoint_;
    bool failed_ = false;
    const sf::Vector2f chunkSize{250.f, 250.f};
    std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> gridMap1_;
    std::map<std::pair<int, int>, std::vector<sf::RectangleShape>> gridMap2_;
};