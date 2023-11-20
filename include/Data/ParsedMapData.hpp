#pragma once

#include <SFML/Graphics.hpp>
#include "Game/Platform.hpp"
#include <vector>

struct ParsedMapData
{
    struct Track
    {
        std::string name;
        std::vector<Platform> platforms;
        std::vector<float> delays;
    };

    sf::Vector2f squareSize;
    std::vector<Track> tracks;
};