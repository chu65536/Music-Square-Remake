#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


class SettingsData {
public:
    void Update();

    unsigned windowSizeVector[2] {1920u, 1080u};
    float squareSizeVector[2] {20.f, 20.f};
    float platformSizeVector[2] {30.f, 10.f};
    float squareColorVector[3] {1.f, 0.f, 0.f};
    float squareSpeedVector[2] {250.f, 250.f};
    float wallsColorVector[3] {0.f, 0.f,0.f};
    float backgroundColorVector[3] {1.f, 1.f, 1.f};
    float chunkSizeVector[2] {250.f, 250.f};
    bool debugWindow = false;

    sf::Vector2f squareSize;
    sf::Vector2f platformSize;
    sf::Vector2f squareSpeed;
    sf::Color squareColor;
    sf::Color backgroundColor;
    sf::Color wallsColor;
    sf::Vector2f chunkSize;
    sf::Vector2u windowSize;
    std::vector<sf::Color> colors{
        sf::Color(0xff0000ff),
        sf::Color(0xffa500ff),
        sf::Color(0xffff00ff),
        sf::Color(0x7cfc00ff),
        sf::Color(0x0000ffff),
        sf::Color(0x7f00ffff),
    };
private:
    void updateColor(sf::Color& color, const float (&vec)[3]);
};