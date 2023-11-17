#pragma once

#include <SFML/Graphics.hpp>


class Camera {
public:
    Camera() = default;
    void Init(sf::RenderWindow* window, const sf::FloatRect& viewport, const sf::Vector2f* target, const sf::Vector2f& position, const sf::Vector2f& size);
    void Update(const sf::Time& dt);
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSize() const;
    void SetView();
    void SetViewport(const sf::FloatRect& viewport);

    float zoom = 1.f;
    float speed = 5.f;
private:
    sf::RenderWindow* m_window;
    const sf::Vector2f* m_targetPosition;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::View m_view;
    sf::FloatRect m_viewport;
};
