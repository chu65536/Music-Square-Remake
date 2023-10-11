#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include "Game/Platform.hpp"
#include "Game/Camera.hpp"
#include "Data/SettingsData.hpp"
#include "Data/SongData.hpp"


struct GameData;

class Map {
public:
    void Init(const SettingsData* settingsData, const SongData* songData);
    void Render(sf::RenderWindow& window, const Camera& cam);
    void Clear();
    const std::vector<Platform>& GetPlatforms() const;
    Platform& GetNextPlatform(float time);
    void addBackground();
    bool isEnd() const;
    size_t GetSize() const;
    bool IsFailed() const;
private:
    void makePlatforms();
    void makeFirstPlatform();
    void handleAttempts(std::unordered_map<unsigned, unsigned>& attempts);
    sf::Vector2f getNextPosition();
    Platform makeNextPlatform(const sf::Vector2f& position, bool& f);
    bool checkCollisions(const Platform& platform);
    std::vector<Platform::Direction> getPossibleDirections(const sf::Vector2f speed) const;
    void revert(std::unordered_map<unsigned, unsigned>& attempts);
    sf::Vector2f getAdaptedSpeed(float dt) const;
    void makeGridMap();
    bool goBack();
    void addNextPlatform(const Platform& platform);
    sf::RectangleShape makeRectangle(const Platform& platform1, const Platform& platform2);

    const SettingsData* m_dataPt;
    const SongData* m_SongDataPt;
    size_t m_curPlatform = 0;
    std::vector<Platform> m_platforms;
    std::vector<sf::RectangleShape> m_background;
    std::vector<sf::RectangleShape> m_backgroundCover;
    bool m_failed = false;
    std::map<std::pair<int, int>, std::vector<Platform*>> m_gridMap;
};