#include <iostream>
#include "camera.hpp"


float lerp(float a, float b, float f) {
    return a + f * (b - a);
}

sf::Vector2f lerp2f(const sf::Vector2f& v1, const sf::Vector2f& v2, float f) {
    return sf::Vector2f{lerp(v1.x, v2.x, f), lerp(v1.y, v2.y, f)};
}

void Camera::Update(const sf::Time& dt) {
    position_ = lerp2f(position_, targetPosition_, speed * dt.asSeconds());
    view_.setSize(size_ * (1.f / zoom));   
    view_.setCenter(position_);
    windowPt_->setView(view_);
}

sf::Vector2f Camera::GetSize() const {
    return (size_ * (1.f / zoom));
}

sf::Vector2f Camera::GetPosition() const {
    return position_;
}