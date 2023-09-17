#include <iostream>
#include "camera.hpp"


float lerp(float a, float b, float f) {
    return a + f * (b - a);
}

sf::Vector2f Lerp(const sf::Vector2f& v1, const sf::Vector2f& v2, float f) {
    return sf::Vector2f{lerp(v1.x, v2.x, f), lerp(v1.y, v2.y, f)};
}

void Camera::Init(sf::RenderWindow* window, Square& target, sf::Vector2f position, sf::Vector2f size) {
    windowPt_ = window;
    targetPt_ = &target;
    position_ = position;
    size_ = size;
}

void Camera::Update(const sf::Time& dt) {
    sf::Vector2f targetPosition = targetPt_->GetPosition();
    position_ = Lerp(position_, targetPosition, smoothSpeed_ * dt.asSeconds());
    view_.setSize(size_ * zoom_);   
    view_.setCenter(position_);
    windowPt_->setView(view_);
}

sf::Vector2f Camera::GetPosition() const {
    return position_;
}

float& Camera::getZoom() {
    return zoom_;
}

float& Camera::getSpeed() {
    return smoothSpeed_;
}