#pragma once

#include <SFML/Graphics.hpp>


class Camera 
{
public:
    Camera(const sf::Vector2f& position, const sf::Vector2f& size);
    void Update(const sf::Time& dt, const sf::Vector2f& newPos);
    void SetView(sf::RenderWindow& window);
    void SetViewport(const sf::FloatRect& viewport);
    void SetPosition(const sf::Vector2f& position);

    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSize() const;

    float zoom = 1.f;
    float speed = 5.f;
private:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::View m_view;
};
