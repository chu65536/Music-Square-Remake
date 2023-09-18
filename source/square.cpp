#include <iostream>
#include "square.hpp"

void Square::Init(const ConfigData data) {
    position_ = data.position;
    speed_ = data.speed;
    rect_ = sf::RectangleShape(data.squareSize);
    rect_.setOrigin(data.squareSize.x / 2, data.squareSize.y / 2);
    rect_.setPosition(position_);
    rect_.setFillColor(sf::Color::White);
}

void Square::Update(float time, const Platform& platform) {
    position_ = platform.GetPosition();
    float deltaTime = time - platform.GetTime();
    Platform::Direction dir = platform.GetDirection();
    switch(dir) {
    case Platform::Direction::Up:
        speed_.y *= (speed_.y < 0 ? -1 : 1);
        break;
    case Platform::Direction::Left:
        speed_.x *= (speed_.x < 0 ? -1 : 1);
        break;
    case Platform::Direction::Down:
        speed_.y *= (speed_.y < 0 ? 1 : -1);
        break;
    case Platform::Direction::Right:
        speed_.x *= (speed_.x < 0 ? 1 : -1);
        break;
    }
    position_ += speed_ * deltaTime;
    rect_.setPosition(position_);
}

void Square::SetSpeed(const sf::Vector2f& speed) {
    speed_ = speed;
}

void Square::Render(sf::RenderWindow& window) {
    window.draw(rect_);
}

sf::Vector2f Square::GetPosition() const {
    return position_;
}