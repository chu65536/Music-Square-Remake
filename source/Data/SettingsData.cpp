#include "Data/SettingsData.hpp"

void SettingsData::Update() {
    if (equalSides) {
        squareSizeVector[1] = squareSizeVector[0];
    }
    squareSize = {(float)squareSizeVector[0], (float)squareSizeVector[1]};

    if (equalSpeeds) {
        squareSpeedVector[1] = squareSpeedVector[0];
    }
    squareSpeed = {(float)squareSpeedVector[0], (float)squareSpeedVector[1]};

    if (platformSizeVector[0] < squareSizeVector[0]) {
        platformSizeVector[0] = squareSizeVector[0];
    }
    if (platformSizeVector[0] < squareSizeVector[1]) {
        platformSizeVector[0] = squareSizeVector[1];
    }
    platformSize = {(float)platformSizeVector[0], (float)platformSizeVector[1]};

    squareOutlineThickness = -squareOutlineThicknessVal;
    platformOutlineThickness = -platformOutlineThicknessVal;

    windowSize = {windowSizeVector[0], windowSizeVector[1]};
    chunkSize = {chunkSizeVector[0], chunkSizeVector[1]};
    updateColor(squareColor, squareColorVector);
    updateColor(wallsColor, wallsColorVector);
    updateColor(backgroundColor, backgroundColorVector);
    updateColor(squareOutlineColor, squareOutlineColorVector);
    updateColor(platformColor, platformColorVector);
    updateColor(platformOutlineColor, platformOutlineColorVector);
}

void SettingsData::updateColor(sf::Color& color, const float (&vec)[3]) {
    color.r = 255.f * vec[0];
    color.g = 255.f * vec[1];
    color.b = 255.f * vec[2];
}