#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <Candle/RadialLight.hpp>
#include "Game/Platform.hpp"


class GameData;

class Square {
public:
    void Init(const GameData& data);
    void Update (float time, Platform& platform);
    void Render(sf::RenderWindow& window);
    void SetSpeed(const sf::Vector2f& speed);
    const std::vector<sf::Vector2f>& GetBounds() const;
    const sf::Vector2f& GetPositionRef() const;
    void CastLight(candle::EdgeVector& bounds);
private:
    sf::Vector2f m_position;
    sf::Vector2f m_speed_;
    sf::RectangleShape m_rect;
    candle::RadialLight m_lightSource;
    std::vector<sf::Vector2f> m_bounds;
};