#include "Data/GameData.hpp"


void GameData::Clear() {
    songData.music.stop();
    songData.delays.clear();
    songData.notes.clear();
    map.Clear();
}

void GameData::Update() {
    squareSpeed = sf::Vector2f(squareSpeedVector[0], squareSpeedVector[1]);
    updateSizes();
    updateColor(squareColor, squareColorVector);
    updateColor(wallsColor, wallsColorVector);
    updateColor(backgroundColor, backgroundColorVector);
}

void GameData::updateColor(sf::Color& color, const float (&v)[3]) {
    color.r = 255.f * v[0];
    color.g = 255.f * v[1];
    color.b = 255.f * v[2];
}

void GameData::updateSizes() {
    squareSize = {squareSizeVector[0], squareSizeVector[1]};
    platformSize = {platformSizeVector[0], platformSizeVector[1]};
    chunkSize = {chunkSizeVector[0], chunkSizeVector[1]};
}