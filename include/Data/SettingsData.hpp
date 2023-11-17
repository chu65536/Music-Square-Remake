#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


class SettingsData 
{
public:
    void Update();

    int squareSizeVector[2] {40, 40};
    bool equalSides = true;

    int squareSpeedVector[2] {500, 500};
    bool equalSpeeds = true;

    float squareColorVector[3] {1.f, 0.f, 0.f};
    float squareOutlineColorVector[3] {0.f, 0.f, 0.f};
    int squareOutlineThicknessVal = 4;


    int platformSizeVector[2] {40, 20};

    float platformColorVector[3] {0.f, 1.f, 0.f};
    float platformOutlineColorVector[3] {0.f, 0.f, 0.f};
    int platformOutlineThicknessVal = 4;

    float wallsColorVector[3] {1.f, 1.f,0.f};
    float wallsOutlineColorVector[3] {0.f, 0.f, 0.f};
    int wallsOutlineThicknessVal = 4;

    float backgroundColorVector[3] {1.f, 1.f, 1.f};

    bool fpsCounter = false;
    bool visiblePlatforms = false;

    // system (inaccessible for user)
    unsigned windowSizeVector[2] {1280u, 720u};
    float chunkSizeVector[2] {500.f, 500.f};
    sf::Vector2f squareSize;
    sf::Vector2f platformSize;
    sf::Vector2f squareSpeed;
    sf::Color squareColor;
    sf::Color backgroundColor;
    sf::Color wallsColor;
    sf::Color squareOutlineColor;
    sf::Color platformColor;
    sf::Color platformOutlineColor;
    sf::Color wallsOutlineColor;
    sf::Vector2f chunkSize;
    sf::Vector2u windowSize;
    float squareOutlineThickness;
    float platformOutlineThickness;
    float wallsOutlineThickness;
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