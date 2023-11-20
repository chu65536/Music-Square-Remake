#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <Candle/RadialLight.hpp>
#include "Game/Platform.hpp"
#include "Data/SettingsData.hpp"


class Square 
{
public:
    Square(const SettingsData& settingsData, const sf::Vector2f& startPoint);
    void Update (float time, Platform& platform);
    void Render(sf::RenderWindow& window);
    void SetSpeed(const sf::Vector2f& speed);
    sf::Vector2f GetPosition() const;
    sf::Color GetColor() const;
private:
    sf::Vector2f m_position;
    sf::Vector2f m_speed;
    sf::RectangleShape m_rect;
    sf::Color m_color;
};