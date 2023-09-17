#include "map.hpp"

Platform::Platform(sf::Vector2f position, Platform::Direction direction, double time, const ConfigData& data) :
    position_(position),
    direction_(direction),
    time_(time),
    rect_(data.platformSize)
{
    rect_.setPosition(position_);    
    rect_.setOrigin(data.platformSize.x / 2, -data.squareSize.y / 2);
    rect_.setFillColor(sf::Color::White);

    switch(direction) {
        case Platform::Direction::Left:
            rect_.setRotation(90.f);
            break;
        case Platform::Direction::Up:
            rect_.setRotation(180.f);
            break;
        case Platform::Direction::Right:
            rect_.setRotation(270.f);
            break;
    }
}

sf::Vector2f Platform::GetPosition() const {
    return position_;
}

sf::RectangleShape Platform::GetRect() const {
    return rect_;
}

float Platform::GetTime() const {
    return time_;
}

Platform::Direction Platform::GetDirection() const {
    return direction_;
}


void Map::makePlatforms(const std::vector<double>& delays) {
    sf::Vector2f position = configDataPt_->position;
    sf::Vector2f speed = configDataPt_->speed;

    platforms_.emplace_back(position, Platform::Direction::Up, 0.0, *configDataPt_);
    for (size_t i = 1; i < delays.size(); ++i) {
        float deltaTime = delays[i] - delays[i - 1];
        position += speed * deltaTime;
        if (speed.y > 0) { 
            platforms_.emplace_back(position, Platform::Direction::Down, delays[i], *configDataPt_);
        }
        else {
            platforms_.emplace_back(position, Platform::Direction::Up, delays[i], *configDataPt_);
        }
        speed.y *= -1;
    }   

}

void Map::Generate(const std::vector<double>& delays, const ConfigData& configData) {
    configDataPt_ = &configData;
    makePlatforms(delays);
}

void Map::Render(sf::RenderWindow& window) const {
    for (size_t i = 0; i < platforms_.size(); ++i) {
        window.draw(platforms_[i].GetRect());
    } 
}

void Map::Clear() {
    platforms_.clear();
    curPlatform = 0;
}

const Platform& Map::GetNextPlatform(float time) {
    while (curPlatform + 1 < platforms_.size() && time > platforms_[curPlatform + 1].GetTime()) {
        curPlatform++;
    }
    return platforms_[curPlatform];
}

bool Map::isEnd() const {
    return platforms_.size() - 1 == curPlatform;
}
