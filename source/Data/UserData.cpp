#include "Data/UserData.hpp"


void UserData::Update() {
    updateColor(squareColor, squareColorVector);
    updateColor(backgroundColor, backgroundColorVector);
    updateColor(wallsColor, wallsColorVector);
}   

void UserData::updateColor(sf::Color& color, const std::vector<float>& vector) {
    color.r = 255 * vector[0];
    color.g = 255 * vector[1];
    color.b = 255 * vector[2]; 
}