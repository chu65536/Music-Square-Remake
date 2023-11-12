#include "Game/Camera.hpp"
#include "Tools/Math.hpp"
#include "Tools/Debug.hpp"


void Camera::Init(sf::RenderWindow* window, const sf::FloatRect& viewport, const sf::Vector2f* target, const sf::Vector2f& position, const sf::Vector2f& size)
{
    m_window = window;
    m_targetPosition = target;
    m_position = position;
    m_size = size;
    m_viewport = viewport;
}

void Camera::Update(const sf::Time& dt) 
{   
    m_position = Math::lerp2f(m_position, *m_targetPosition, speed * dt.asSeconds());
    m_view.setSize(sf::Vector2f(m_size.x * m_viewport.width, m_size.y * m_viewport.height));   
    m_view.setCenter(m_position);
    m_view.setViewport(m_viewport);
}

sf::Vector2f Camera::GetSize() const 
{
    return sf::Vector2f(m_size.x * m_viewport.width, m_size.y * m_viewport.height);
}

sf::Vector2f Camera::GetPosition() const 
{
    return m_position;
}

void Camera::SetView()
{
    m_window->setView(m_view);
}