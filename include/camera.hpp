#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "square.hpp"


class Camera {
public:
    template<typename T>
    Camera(sf::RenderWindow* window, const T& target, const sf::Vector2f& position, const sf::Vector2f& size);
    void Update(const sf::Time& dt);
    sf::Vector2f GetPosition() const;

    float zoom = 2.f;
    float speed = 5.f;
private:
    sf::RenderWindow* windowPt_ = nullptr;
    const sf::Vector2f& targetPosition_;
    sf::Vector2f position_;
    sf::Vector2f size_;
    sf::View view_;
};

template<typename T>
inline Camera::Camera(sf::RenderWindow* window, const T& target, const sf::Vector2f& position, const sf::Vector2f& size) :
    windowPt_(window),
    targetPosition_(target.GetPositionRef()),
    position_(position),
    size_(size) {
}
