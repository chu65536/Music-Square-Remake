#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include "MidiFile.h"
#include "Game/Map.hpp"
#include "Game/Square.hpp"
#include "Adds/Camera.hpp"
#include "Data/SongData.hpp"


class GameData {
public:
    void Clear();

    sf::RenderWindow* windowPt;
    SongData songData;
    Square square;
    Map map;
};