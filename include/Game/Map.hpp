#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include "Game/Platform.hpp"
#include "Game/Camera.hpp"
#include "Data/SettingsData.hpp"
#include "Data/SongData.hpp"
#include "Game/MapGenerator.hpp"
#include "Data/ParsedMapData.hpp"


class Map 
{
public:
    Map(const SettingsData& settingsData, const SongData::Track& trackData, const sf::Vector2f& startPoint);
    Map(const SettingsData& settingsData, const ParsedMapData::Track& trackData);
    void Render(sf::RenderWindow& window, const Camera& cam);
    void Clear();
    Platform& GetNextPlatform(float time);

private:   
    size_t m_curPlatform = 0;
    std::vector<Platform> m_platforms;
    std::vector<sf::RectangleShape> m_background;
    std::vector<sf::RectangleShape> m_backgroundCover;
    sf::RectangleShape m_wallsRect;
    sf::Vector2f m_chunkSize;
    std::vector<GridMap> m_gridMaps;
};