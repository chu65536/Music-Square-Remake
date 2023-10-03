#include "Data/SettingsData.hpp"

void SettingsData::Update() {
    squareSize = {squareSizeVector[0], squareSizeVector[1]};
    squareSpeed = {squareSpeedVector[0], squareSpeedVector[1]};
    platformSize = {platformSizeVector[0], platformSizeVector[1]};
    windowSize = {windowSizeVector[0], windowSizeVector[1]};
    chunkSize = {chunkSizeVector[0], chunkSizeVector[1]};
    updateColor(squareColor, squareColorVector);
    updateColor(wallsColor, wallsColorVector);
    updateColor(backgroundColor, backgroundColorVector);
}

void SettingsData::updateColor(sf::Color& color, const float (&vec)[3]) {
    color.r = 255.f * vec[0];
    color.g = 255.f * vec[1];
    color.b = 255.f * vec[2];
}