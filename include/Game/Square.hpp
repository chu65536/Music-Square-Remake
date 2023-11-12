#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <Candle/RadialLight.hpp>
#include "Game/Platform.hpp"
#include "Data/SettingsData.hpp"


class Square 
{
public:
    void Init(const SettingsData& settingsData, const sf::Vector2f& startPoint);
    void Update (float time, Platform& platform);
    void Render(sf::RenderWindow& window);
    void SetSpeed(const sf::Vector2f& speed);
    const std::vector<sf::Vector2f>& GetBounds() const;
    const sf::Vector2f* GetPositionRef() const;
private:
    sf::Vector2f m_position;
    sf::Vector2f m_speed_;
    sf::RectangleShape m_rect;
    std::vector<sf::Vector2f> m_bounds;
};