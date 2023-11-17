#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include "Game/Square.hpp"
#include "Game/Map.hpp"
#include "Game/Camera.hpp"
#include "MidiFile.h"
#include "Data/SongData.hpp"

struct GameData 
{
    struct Screen
    {   
        int id;
        Square square;
        Map map;
        Camera camera;
        float beginTime;
        float endTime;
        bool used = false;
    };
    void Clear();

    sf::RenderWindow* windowPt;
    SongData songData;
    std::vector<Screen> screens;
};