#pragma once

#include <SFML/Graphics.hpp>
#include "configdata.hpp"
#include "map.hpp"


class Square {
public:
    void Init(const ConfigData data);
    void Update (float time, const Platform& platform);
    void Render(sf::RenderWindow& window);
    void MultiplySpeed(sf::Vector2i multi);
    sf::Vector2f GetPosition() const;
private:
    sf::Vector2f position_;
    sf::Vector2f speed_;
    sf::RectangleShape rect_; 
};