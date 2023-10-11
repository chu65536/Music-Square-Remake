#pragma once

#include <SFML/Graphics.hpp>
#include <Candle/RadialLight.hpp>
#include <vector>


class Platform {
public:
    enum class Direction { Down, Left, Up, Right };
    struct Data {
        sf::Vector2f position;
        double time;
        sf::Vector2f size;
        std::vector<Platform::Direction> directions;
        sf::Color color;
        sf::Vector2f speedBefore;
        sf::Vector2f squareSize;
    };
    Platform(Data&& data);
    sf::Vector2f GetPosition() const;
    const sf::RectangleShape& GetRect() const;
    float GetTime() const;
    Platform::Direction GetDirection() const;
    sf::Vector2f GetSpeedBefore() const;
    sf::Vector2f GetSpeedAfter() const;
    void AdaptSpeedAfter(const sf::Vector2f& speed);
    bool TryAnotherDirection();
    const std::vector<sf::Vector2f>& GetBounds() const;
    void AddCandleBounds(candle::EdgeVector& pool) const;
    void Render(sf::RenderWindow&);
    void MakeActive();
private:
    void setDirection();
    void setSpeedAfter();
    void rotate();

    const Data m_data;
    const sf::Vector2f m_position;
    const double m_time;
    sf::Vector2f m_size;
    sf::Color m_color;
    Platform::Direction m_direction;
    sf::RectangleShape m_rect;
    const sf::Vector2f m_speedBefore;
    sf::Vector2f m_speedAfter;
    std::vector<Direction> m_possibleDirections;
    std::vector<sf::Vector2f> m_bounds;
};