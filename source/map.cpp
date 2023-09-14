#include "map.hpp"

Platform::Platform(sf::Vector2f position, Platform::Direction direction, double time) :
    position_(position),
    direction_(direction),
    time_(time)
{
    rect_ = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
    rect_.setPosition(position_);    
}

sf::RectangleShape Platform::GetRect() const {
    return rect_;
}

void Map::Generate(const std::vector<double>& delays) {
    platforms_.emplace_back(sf::Vector2f(0.f, 0.f), Platform::Direction::Down, 0.f);
}

void Map::Render(sf::RenderWindow& window) const {
    for (size_t i = 0; i < platforms_.size(); ++i) {
        window.draw(platforms_[i].GetRect());
    } 
}
