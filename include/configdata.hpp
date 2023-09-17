#pragma once

#include <SFML/Graphics.hpp>


class ConfigData {
public:
    sf::Vector2f windowSize{800.f, 800.f};
    sf::Vector2f squareSize{20.f, 20.f};
    sf::Vector2f platformSize{20.f, 10.f};
    sf::Vector2f position{0.f, 100.f};
    sf::Vector2f speed{200.f, 200.f};
    float cameraZoom = 1.f;
    bool debugWindow = true;
};