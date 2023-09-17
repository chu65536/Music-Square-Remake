#pragma once

#include <SFML/Graphics.hpp>
#include "square.hpp"


class Camera {
public:
    void Init(sf::RenderWindow* window, Square& target, sf::Vector2f position, sf::Vector2f size);
    void Update(const sf::Time& dt);
    float& getZoom();
    float& getSpeed();
    sf::Vector2f GetPosition() const;
private:
    sf::Vector2f position_;
    sf::Vector2f size_;
    sf::RenderWindow* windowPt_ = nullptr;
    sf::View view_;
    const Square* targetPt_ = nullptr;
    float zoom_ = 1.f;
    float smoothSpeed_ = 2.f;
};