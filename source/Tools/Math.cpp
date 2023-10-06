#include "Tools/Math.hpp"
#include <cmath>

float Math::lerp(float a, float b, float f) {
    return a + f * (b - a);
}

sf::Vector2f Math::lerp2f(const sf::Vector2f& v1, const sf::Vector2f& v2, float f) {
    return sf::Vector2f{ lerp(v1.x, v2.x, f), lerp(v1.y, v2.y, f) };
}

std::vector<sf::Vector2f> Math::GetBounds(const sf::RectangleShape& shape) {
    sf::Vector2f position = shape.getPosition();
    sf::Vector2f size = shape.getSize();
    float angle = shape.getRotation();

    sf::Vector2f topLeft = shape.getPosition() - shape.getOrigin();
    sf::Vector2f topRight(topLeft.x + size.x, topLeft.y);
    sf::Vector2f bottomRight = topLeft + size;
    sf::Vector2f bottomLeft(topLeft.x, topLeft.y + size.y);
    
    std::vector<sf::Vector2f> bounds = {topLeft, topRight, bottomRight, bottomLeft};
    rotateBounds(bounds, position, angle);
    return bounds;
}

void Math::rotatePoint(sf::Vector2f& point, const sf::Vector2f& center, float angle) {
    angle = angle * M_PI / 180.f;
    float x = cos(angle) * (point.x - center.x) - sin(angle) * (point.y - center.y);
    float y = sin(angle) * (point.x - center.x) + cos(angle) * (point.y - center.y);
    point.x = center.x + x;
    point.y = center.y + y;
}

void Math::rotateBounds(std::vector<sf::Vector2f>& bounds, const sf::Vector2f& center, float angle) {
    for (size_t i = 0; i < bounds.size(); ++i) {
        rotatePoint(bounds[i], center, angle);
    }
}