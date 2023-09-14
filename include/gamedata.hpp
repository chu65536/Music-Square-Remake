#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include "map.hpp"


class GameData {
public:
    std::string songName;
    sf::Music music;
    Map map;
};