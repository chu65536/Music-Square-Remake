#include "Adds/Math.hpp"

float Math::lerp(float a, float b, float f) {
    return a + f * (b - a);
}

sf::Vector2f Math::lerp2f(const sf::Vector2f& v1, const sf::Vector2f& v2, float f) {
    return sf::Vector2f{ lerp(v1.x, v2.x, f), lerp(v1.y, v2.y, f) };
}

std::vector<sf::Vector2f> Math::GetBounds(const sf::RectangleShape& shape) {
    std::vector<sf::Vector2f> ret;
    return ret;
}