#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include "MidiFile.h"
#include "Game/map.hpp"
#include "Game/Square.hpp"
#include "Adds/Camera.hpp"


struct GameData {
    void Clear();
    sf::RenderWindow* windowPt;
    std::string songName;
    sf::Music music;
    smf::MidiFile midi;
    Square square;
    Map map;
};