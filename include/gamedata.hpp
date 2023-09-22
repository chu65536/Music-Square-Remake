#pragma once

#include <string>
#include <SFML/Audio.hpp>
#include "map.hpp"
#include "square.hpp"
#include "camera.hpp"


class GameData {
public:
    void Clear();
    sf::RenderWindow* windowPt;
    std::string songName;
    sf::Music music;
    Square square;
    Map map;
};