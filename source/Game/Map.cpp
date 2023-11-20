#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <Tools/Math.hpp>
#include "Game/Map.hpp"
#include "Data/GameData.hpp"
#include "Tools/Debug.hpp"


Map::Map(const SettingsData& settingsData, const SongData::Track& trackData, const sf::Vector2f& startPoint) :
    m_chunkSize(settingsData.chunkSize)
{
    MapGenerator generator(settingsData);
    generator.Generate(trackData, startPoint);
    MapData data = generator.MoveData();

    m_platforms = std::move(data.platforms);
    m_background = std::move(data.background);
    m_backgroundCover = std::move(data.backgroundCover);
    m_wallsRect = std::move(data.wallsRect);
    m_gridMaps = std::move(data.gridMaps);
}

Map::Map(const SettingsData& settingsData, const ParsedMapData::Track& parsedTrackData) :
    m_chunkSize(settingsData.chunkSize)
{
    MapGenerator generator(settingsData);
    generator.Generate(parsedTrackData);
    MapData data = generator.MoveData();

    m_platforms = std::move(data.platforms);
    m_background = std::move(data.background);
    m_backgroundCover = std::move(data.backgroundCover);
    m_wallsRect = std::move(data.wallsRect);
    m_gridMaps = std::move(data.gridMaps);
}

void Map::Render(sf::RenderWindow& window, const Camera& cam) 
{   
    sf::Vector2f camSz = cam.GetSize();
    sf::Vector2f camPos = cam.GetPosition(); 

    int l = (camPos.x - camSz.x) / m_chunkSize.x;
    int r = (camPos.x + camSz.x) / m_chunkSize.x;
    int u = (camPos.y - camSz.y) / m_chunkSize.y;
    int d = (camPos.y + camSz.y) / m_chunkSize.y;

    window.draw(m_wallsRect);
    for (auto& gridMap: m_gridMaps)
    {
        for (int x = l; x <= r; ++x)
        {
            for (int y = u; y <= d; ++y)
            { 
                for (auto& rect: gridMap[{x, y}])
                {
                    window.draw(rect);
                }
            }
        }
    }
}

Platform& Map::GetNextPlatform(float time) 
{
    while (m_curPlatform + 1 < m_platforms.size() && time > m_platforms[m_curPlatform + 1].GetTime()) 
    {
        m_curPlatform++;
    }
    return m_platforms[m_curPlatform];
}

void Map::Clear() {
    m_platforms.clear();
    m_background.clear();
    m_backgroundCover.clear();
    m_gridMaps.clear();
    m_curPlatform = 0;
}





