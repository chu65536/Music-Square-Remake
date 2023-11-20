#include "Game/Camera.hpp"
#include "Tools/Math.hpp"
#include "Tools/Debug.hpp"


Camera::Camera(const sf::Vector2f& position, const sf::Vector2f& size) :
    m_position(position),
    m_size(size)
{
}

void Camera::Update(const sf::Time& dt, const sf::Vector2f& newPos) 
{   
    m_position = Math::lerp2f(m_position, newPos, speed * dt.asSeconds());
    m_view.setSize(m_size);   
    m_view.setCenter(m_position);
}

void Camera::SetView(sf::RenderWindow& window)
{
    window.setView(m_view);
}

void Camera::SetViewport(const sf::FloatRect& viewport)
{
    m_view.setViewport(viewport);
    m_view.setSize(m_size.x * viewport.width, m_size.y * viewport.height);
}

void Camera::SetPosition(const sf::Vector2f& position)
{
    m_position = position;
}

sf::Vector2f Camera::GetPosition() const
{
    return m_position;
}

sf::Vector2f Camera::GetSize() const
{
    return m_size;
}