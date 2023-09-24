#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


namespace Math {
float lerp(float a, float b, float t);
sf::Vector2f lerp2f(const sf::Vector2f& v1, const sf::Vector2f& v2, float f);
std::vector<sf::Vector2f> GetBounds(const sf::RectangleShape& shape);
}
