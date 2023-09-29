#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include "MidiFile.h"
#include "Game/Map.hpp"
#include "Game/Square.hpp"
#include "Adds/Camera.hpp"
#include "Data/SongData.hpp"


struct GameData {
    float squareSizeVector[2] = {20, 20};
    float squareSpeedVector[2] = {250.f, 250.f};
    float squareColorVector[3] = {1.f, 1.f, 1.f};
    float platformSizeVector[2] = {30.f, 10.f};
    float backgroundColorVector[3] = {0.2f, 0.2f, 0.2f};
    float wallsColorVector[3] = {0.f, 0.f, 0.f};
    float chunkSizeVector[2] = {250.f, 250.f};
    bool debugWindow = true;

    sf::Vector2u windowSize {1920u, 1080u};
    sf::Vector2f position {0.f, 0.f};
    sf::Vector2f squareSize;
    sf::Vector2f squareSpeed;
    sf::Color squareColor;
    sf::Color squareOutlineColor {sf::Color::Black};
    float squareOutlineThickness = 2.f;
    sf::Vector2f platformSize;
    sf::Color platformColor {sf::Color::Blue};
    sf::Color backgroundColor;
    sf::Color wallsColor;
    sf::Vector2f chunkSize;

    std::vector<sf::Color> colors{
        sf::Color(0xff0000ff),
        sf::Color(0xffa500ff),
        sf::Color(0xffff00ff),
        sf::Color(0x7cfc00ff),
        sf::Color(0x0000ffff),
        sf::Color(0x7f00ffff),
    };

    sf::RenderWindow* windowPt;
    SongData songData;
    Square square;
    Map map;

    void Clear();
    void Update();
private:
    void updateColor(sf::Color& color, const float (&v)[3]);
    void updateSizes();
};