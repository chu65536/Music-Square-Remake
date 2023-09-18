#include <iostream>
#include <chrono>
#include "map.hpp"


void Map::Init(const std::vector<double>& delays, const ConfigData* configData, Square* square) {
    configDataPt_ = configData;
    squarePt_ = square;
    makePlatforms(delays);
}

void Map::makePlatforms(const std::vector<double>& delays) {
    std::chrono::time_point<std::chrono::system_clock> timerStart, timerEnd;
    timerStart = std::chrono::system_clock::now();

    sf::Vector2f speed = configDataPt_->speed;
    makeFirstPlatform(speed);
    size_t currentSize = 1;
    
    std::vector<sf::Vector2f> tmp = {sf::Vector2f()};
    while (currentSize != delays.size()) {
        std::cout << "Map generation: " << int(float(currentSize) / delays.size() * 100) << std::endl; 
        sf::Vector2f prevPos = platforms_[currentSize - 1].GetPosition();
        float deltaTime = delays[currentSize] - delays[currentSize - 1];
        sf::Vector2f curPos = prevPos + speed * deltaTime;
        Platform tryPlatform = makeNextPlatform(curPos, delays[currentSize], speed);
        bool collision = checkCollisions(tryPlatform);
        if (collision) {
            while(currentSize != 0 && platforms_[currentSize - 1].TryAnotherDir() == false) {
                platforms_.pop_back();
                tmp.pop_back();
                currentSize--;
            }
            if (currentSize == 0) {
                std::cout << "Error: can not generate map" << std::endl;
                return;
            }
            speed = tmp[currentSize - 1];
            updateDirection(speed, platforms_[currentSize - 1].GetDirection());
            continue;
        }

        tmp.push_back(speed);
        platforms_.emplace_back(tryPlatform);
        updateDirection(speed, platforms_[currentSize].GetDirection());
        currentSize++;
    } 

    timerEnd = std::chrono::system_clock::now();  
    std::chrono::duration<double> elapsed_seconds = timerEnd - timerStart;
    std::cout << "Map gengerated, elapsed time: " << elapsed_seconds.count() << std::endl;
}

void Map::makeFirstPlatform(sf::Vector2f& speed) {
    sf::Vector2f position = configDataPt_->position;
    std::vector<Platform::Direction> dirs = {Platform::Direction::Down, Platform::Direction::Left, Platform::Direction::Up, Platform::Direction::Right};
    platforms_.emplace_back(position, dirs, 0.0, configDataPt_);

    int flip[2] = {1, -1};
    switch (platforms_[0].GetDirection()) {
    case Platform::Direction::Down:
        speed.x *= flip[rand() % 2]; 
        speed.y = -abs(speed.y);
        break;
    case Platform::Direction::Left:
        speed.x = abs(speed.x); 
        speed.y *= flip[rand() % 2];
        break;
    case Platform::Direction::Up:
        speed.x *= flip[rand() % 2]; 
        speed.y = abs(speed.y);
        break;
    case Platform::Direction::Right:
        speed.x = -abs(speed.x); 
        speed.y *= flip[rand() % 2];
        break;
    }

    squarePt_->SetSpeed(speed);
}

Platform Map::makeNextPlatform(const sf::Vector2f& position, double time, const sf::Vector2f& speed) {
    std::vector<Platform::Direction> possibleDirs;
    if (speed.x > 0) {
        possibleDirs.emplace_back(Platform::Direction::Right);
    }
    else {
        possibleDirs.emplace_back(Platform::Direction::Left);    
    }
    if (speed.y > 0) {
        possibleDirs.emplace_back(Platform::Direction::Down);    
    }
    else {
        possibleDirs.emplace_back(Platform::Direction::Up);
    }

    Platform ret(position, possibleDirs, time, configDataPt_);
    return ret;
}

bool Map::checkCollisions(const Platform& platform) {
    sf::Vector2f pos = platform.GetPosition();

    for (size_t i = 1; i < platforms_.size(); ++i) {
        sf::Vector2f pos1 = platforms_[i - 1].GetPosition();
        sf::Vector2f pos2 = platforms_[i].GetPosition();

        float x1 = std::min(pos1.x, pos2.x) - configDataPt_->squareSize.x;
        float y1 = std::min(pos1.y, pos2.y) - configDataPt_->squareSize.y;
        float x2 = std::max(pos1.x, pos2.x) + configDataPt_->squareSize.x;
        float y2 = std::max(pos1.y, pos2.y) + configDataPt_->squareSize.y;

        if (x1 <= pos.x && pos.x <= x2 && y1 <= pos.y && pos.y <= y2)
            return true;
    }

    return false;
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

void Map::updateDirection(sf::Vector2f& speed, Platform::Direction dir) {
    if (dir == Platform::Direction::Up || dir == Platform::Direction::Down) {
        speed.y *= -1;
    }
    if (dir == Platform::Direction::Left || dir == Platform::Direction::Right) {
        speed.x *= -1;
    }
}
