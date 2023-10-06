#include "Game/Camera.hpp"
#include "Tools/Math.hpp"


void Camera::Update(const sf::Time& dt) {
    m_position = Math::lerp2f(m_position, m_targetPosition, speed * dt.asSeconds());
    m_view.setSize(m_size * (1.f / zoom));   
    m_view.setCenter(m_position);
    m_window.setView(m_view);
}

sf::Vector2f Camera::GetSize() const {
    return (m_size * (1.f / zoom));
}

sf::Vector2f Camera::GetPosition() const {
    return m_position;
}