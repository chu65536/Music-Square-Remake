#pragma once

#include "Data/SettingsData.hpp"
#include "Data/SongData.hpp"
#include "Game/Platform.hpp"
#include <SFML/Graphics.hpp>
#include <Data/ParsedMapData.hpp>

struct VectorHash 
{
    template<typename T>
    std::size_t operator()(const sf::Vector2<T>& v) const
    {
        return std::hash<T>()(v.x) ^ std::hash<T>()(v.y);
    }
};

using GridMap = std::unordered_map<sf::Vector2i, std::vector<sf::RectangleShape>, VectorHash>;

struct MapData
{
    std::vector<Platform> platforms;
    std::vector<sf::RectangleShape> background;
    std::vector<sf::RectangleShape> backgroundCover;
    sf::RectangleShape wallsRect;
    std::vector<GridMap> gridMaps;      
};


class MapGenerator
{
public:
    MapGenerator(const SettingsData& settingsData);
    bool Generate(const SongData::Track& trackData, const sf::Vector2f& startPoint);
    bool Generate(const ParsedMapData::Track& parsedTrackData);
    void Export(std::ofstream& file);
    MapData&& MoveData();
private:
    void makeFirstPlatform();
    void handleAttempts(std::unordered_map<int, int>& attempts);
    sf::Vector2f getNextPosition();
    Platform makeNextPlatform(const sf::Vector2f& position, bool& remakeLastPlatform);
    bool checkCollisions(const Platform& platform);
    bool goBack();
    void addBackground();
    void makeWalls(); 
    void makeGridMap();
    std::vector<Platform::Direction> getPossibleDirections(const sf::Vector2f speed) const;
    sf::Vector2f getAdaptedSpeed(float dt) const;
    sf::RectangleShape makeRectangle(const Platform& platform1, const Platform& platform2);
    GridMap calcGridMap(std::vector<sf::RectangleShape>& rects);
    void makeBackgroundByPlatforms();

    const SettingsData& m_settingsData;
    const SongData::Track* m_trackData;
    sf::Vector2f m_startPoint;

    std::vector<Platform> m_platforms;
    std::vector<sf::RectangleShape> m_background;
    std::vector<sf::RectangleShape> m_backgroundCover;
    sf::RectangleShape m_wallsRect;
    std::vector<GridMap> m_gridMaps;

    MapData m_data;
};