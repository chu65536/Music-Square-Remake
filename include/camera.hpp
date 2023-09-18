#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "square.hpp"


class Camera {
public:
    void Init(sf::RenderWindow* window, Square& target, sf::Vector2f position, sf::Vector2f size);
    void Update(const sf::Time& dt);
    sf::Vector2f GetPosition() const;

    float zoom = 1.f;
    float speed = 5.f;
private:
    sf::RenderWindow* windowPt_ = nullptr;
    const Square* targetPt_ = nullptr;
    sf::Vector2f position_;
    sf::Vector2f size_;
    sf::View view_;
};