#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include "map.hpp"
#include "square.hpp"


class GameData {
public:
    void Clear();
    std::string songName;
    sf::Music music;
    Square square;
    Map map;
};