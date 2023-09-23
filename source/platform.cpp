#include <algorithm>
#include "platform.hpp"


Platform::Platform(
    sf::Vector2f position,
    std::vector<Platform::Direction> dirs,
    double time,
    sf::Vector2f speedBefore,
    const ConfigData& data
)   :
    data_(data),
    position_(position),
    size_(data.platformSize),
    possibleDirections_(dirs),
    time_(time),
    speedBefore_(speedBefore)
{
    rect_.setPosition(position_);    
    rect_.setFillColor(sf::Color::Blue);

    setDirection();
}

void Platform::setDirection() {
    direction_ = possibleDirections_[rand() % possibleDirections_.size()];
    possibleDirections_.erase(std::remove(possibleDirections_.begin(), possibleDirections_.end(), direction_), possibleDirections_.end());
    switch(direction_) {
    case Platform::Direction::Down:
        size_ = sf::Vector2f(data_.squareSize.x, data_.platformSize.y);
        rect_.setSize(size_);
        rect_.setOrigin(size_.x / 2, -data_.squareSize.y / 2);
        rect_.setRotation(0.f);
        break;
    case Platform::Direction::Left:
        size_ = sf::Vector2f(data_.squareSize.y, data_.platformSize.y);
        rect_.setSize(size_);
        rect_.setOrigin(size_.x / 2, -data_.squareSize.x / 2);
        rect_.setRotation(90.f);
        break;
    case Platform::Direction::Up:
        size_ = sf::Vector2f(data_.squareSize.x, data_.platformSize.y);
        rect_.setSize(size_);
        rect_.setOrigin(size_.x / 2, -data_.squareSize.y / 2);
        rect_.setRotation(180.f);
        break;
    case Platform::Direction::Right: 
        size_ = sf::Vector2f(data_.squareSize.y, data_.platformSize.y);
        rect_.setSize(size_);
        rect_.setOrigin(size_.x / 2, -data_.squareSize.x / 2);
        rect_.setRotation(270.f);
        break;
    }

    setSpeedAfter();
}

void Platform::setSpeedAfter() {
    speedAfter_ = speedBefore_;
    if (direction_ == Platform::Direction::Up || direction_ == Platform::Direction::Down) {
        speedAfter_.y *= -1;
    }
    if (direction_ == Platform::Direction::Left || direction_ == Platform::Direction::Right) {
        speedAfter_.x *= -1;
    }
}

void Platform::AdaptSpeedAfter(sf::Vector2f speed) {
    speed.x *= (speedAfter_.x > 0 ? 1 : -1);
    speed.y *= (speedAfter_.y > 0 ? 1 : -1);

    speedAfter_ = speed;
}

sf::Vector2f Platform::GetPosition() const {
    return position_;
}

const sf::RectangleShape& Platform::GetRect() const {
    return rect_;
}

float Platform::GetTime() const {
    return time_;
}

Platform::Direction Platform::GetDirection() const {
    return direction_;
}

sf::Vector2f Platform::GetSpeedBefore() const {
    return speedBefore_;
}

sf::Vector2f Platform::GetSpeedAfter() const {
    return speedAfter_;
}

bool Platform::TryAnotherDir() {
    if (possibleDirections_.size() == 0) {
        return false;
    }
    setDirection();
    return true;
}