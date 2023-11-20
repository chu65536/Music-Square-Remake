#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include "Game/Square.hpp"
#include "Game/Map.hpp"
#include "Game/Camera.hpp"
#include "MidiFile.h"
#include "Data/SongData.hpp"
#include "Game/Screen.hpp"

struct GameData 
{
    void Clear();

    const std::string songsFolder = "../resources/songs/";
    const std::string fontPath = "../resources/fonts/SadanaSquare.ttf";

    sf::RenderWindow* windowPt;
    SongData songData;
    std::vector<Screen> screens;
    std::string chosenMapPath;
    std::string newMapName;
    bool newMap = false;
};