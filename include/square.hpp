#pragma once

#include <SFML/Graphics.hpp>
#include "configdata.hpp"
#include "platform.hpp"


class Square {
public:
    void Init(const ConfigData data);
    void Update (float time, const Platform& platform);
    void Render(sf::RenderWindow& window);
    void SetSpeed(const sf::Vector2f& speed);
    sf::Vector2f GetPosition() const;
    const sf::Vector2f& GetPositionRef() const;
private:
    sf::Vector2f position_{0.f, 0.f};
    sf::Vector2f speed_{0.f, 0.f};
    sf::RectangleShape rect_; 
};