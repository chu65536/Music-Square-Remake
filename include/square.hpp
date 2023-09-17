#pragma once

#include <SFML/Graphics.hpp>
#include "configdata.hpp"
#include "map.hpp"


class Square {
public:
    void Init(const ConfigData data);
    void Update (float time, const Platform& platform);
    void Render(sf::RenderWindow& window);
    sf::Vector2f GetPosition() const;
private:
    sf::Vector2f position_{0.f, 0.f};
    sf::Vector2f speed_{0.f, 0.f};
    sf::RectangleShape rect_; 
};