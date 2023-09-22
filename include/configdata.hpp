#pragma once

#include <SFML/Graphics.hpp>


class ConfigData {
public:
    sf::Vector2f windowSize{1920.f, 1080.f};
    sf::Vector2f squareSize{20.f, 20.f};
    sf::Vector2f platformSize{20.f, 10.f};
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f speed{300.f, 300.f};
    bool debugWindow = true;
};