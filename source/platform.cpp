#include <algorithm>
#include "platform.hpp"


Platform::Platform(sf::Vector2f position, std::vector<Platform::Direction> dirs, double time, const ConfigData* data) :
    position_(position),
    possibleDirections_(dirs),
    time_(time),
    rect_(data->platformSize)
{
    rect_.setPosition(position_);    
    rect_.setOrigin(data->platformSize.x / 2, -data->squareSize.y / 2);

    setDirection();
}

void Platform::setDirection() {
    direction_ = possibleDirections_[rand() % possibleDirections_.size()];
    possibleDirections_.erase(std::remove(possibleDirections_.begin(), possibleDirections_.end(), direction_), possibleDirections_.end());
    switch(direction_) {
    case Platform::Direction::Down:
        rect_.setRotation(0.f);
        rect_.setFillColor(sf::Color::Red);
        break;
    case Platform::Direction::Left:
        rect_.setRotation(90.f);
        rect_.setFillColor(sf::Color::Green);
        break;
    case Platform::Direction::Up:
        rect_.setRotation(180.f);
        rect_.setFillColor(sf::Color::Blue);
        break;
    case Platform::Direction::Right: 
        rect_.setFillColor(sf::Color::Yellow);
        rect_.setRotation(270.f);
        break;
    }
}

sf::Vector2f Platform::GetPosition() const {
    return position_;
}

sf::RectangleShape Platform::GetRect() const {
    return rect_;
}

float Platform::GetTime() const {
    return time_;
}

Platform::Direction Platform::GetDirection() const {
    return direction_;
}

bool Platform::TryAnotherDir() {
    if (possibleDirections_.size() == 0) {
        return false;
    }
    setDirection();
    return true;
}