#pragma once

#include <SFML/Graphics.hpp>


class Camera {
public:
    template<typename T>
    Camera(sf::RenderWindow& window, const T& target, const sf::Vector2f& position, const sf::Vector2u& size);
    void Update(const sf::Time& dt);
    sf::Vector2f GetPosition() const;
    sf::Vector2f GetSize() const;

    float zoom = 2.f;
    float speed = 5.f;
private:
    sf::RenderWindow& m_window;
    const sf::Vector2f& m_targetPosition;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::View m_view;
};

template<typename T>
inline Camera::Camera(sf::RenderWindow& window, const T& target, const sf::Vector2f& position, const sf::Vector2u& size) :
    m_window(window),
    m_targetPosition(target.GetPositionRef()),
    m_position(position),
    m_size(size) {
}
