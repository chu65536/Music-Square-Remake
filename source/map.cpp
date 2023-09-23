#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include "map.hpp"


void Map::Init(const std::vector<double>& delays, const ConfigData* configData, Square* square, std::mutex& m) {
    configDataPt_ = configData;
    squarePt_ = square;
    makePlatforms(delays, m);
}

void Map::makePlatforms(const std::vector<double>& delays, std::mutex& m) {
    std::chrono::time_point<std::chrono::system_clock> timerStart, timerEnd;
    timerStart = std::chrono::system_clock::now();

    makeFirstPlatform();
    size_t currentSize = 1;
    const sf::Vector2f fixedDistance(50.f, 50.f);  

    std::unordered_map<int, int> attempts;
    while (currentSize != delays.size()) {
        {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "Map generation: " << int(float(currentSize) / delays.size() * 100) << std::endl; 
            attempts[currentSize]++;
            if (attempts[currentSize] > 100) {
                revert(attempts, currentSize);
            }
            float deltaTime = delays[currentSize] - delays[currentSize - 1];
            sf::Vector2f adaptedSpeed = getAdaptedSpeed(deltaTime);
            //sf::Vector2f adaptedSpeed = fixedDistance / deltaTime;
            platforms_[currentSize - 1].AdaptSpeedAfter(adaptedSpeed);
            sf::Vector2f speed = platforms_[currentSize - 1].GetSpeedAfter(); 
            sf::Vector2f prevPos = platforms_[currentSize - 1].GetPosition();
            sf::Vector2f newPos = prevPos + speed * deltaTime;
            Platform tryPlatform = makeNextPlatform(newPos, delays[currentSize], speed);
            bool collision = checkCollisions(tryPlatform);
            if (collision) {
                while(currentSize != 1 && platforms_[currentSize - 1].TryAnotherDir() == false) {
                    platforms_.pop_back();
                    background_.pop_back();
                    backgroundCover_.pop_back();
                    currentSize--;
                }
                if (currentSize == 1) {
                    failed_ = true;
                    std::cout << "Error: can not generate map" << std::endl;
                    return;
                }
                continue;
            }
            platforms_.emplace_back(tryPlatform);
            addBackground();
            centerPoint_ = newPos;
            currentSize++;
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } 
    makeGridMap();
    timerEnd = std::chrono::system_clock::now();  
    std::chrono::duration<double> elapsed_seconds = timerEnd - timerStart;
    std::cout << "Map gengerated, elapsed time: " << elapsed_seconds.count() << std::endl;
}

void Map::makeFirstPlatform() {
    sf::Vector2f position = configDataPt_->position;
    sf::Vector2f speed = configDataPt_->speed;
    speed.x *= (rand() % 2 ? -1: 1);
    speed.y *= (rand() % 2 ? -1: 1);
    std::vector<Platform::Direction> dirs = getPossibleDirs(speed);
    platforms_.emplace_back(position, dirs, 0.0, speed, *configDataPt_);
    speed = platforms_[0].GetSpeedAfter();
    squarePt_->SetSpeed(speed);
}

Platform Map::makeNextPlatform(const sf::Vector2f& position, double time, const sf::Vector2f& speed) {
    std::vector<Platform::Direction> possibleDirs = getPossibleDirs(speed);
    Platform ret(position, possibleDirs, time, speed, *configDataPt_);
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

    sf::Vector2f last = platforms_[GetSize() - 1].GetPosition();
    for (size_t i = 0; i < platforms_.size() - 1; ++i) {
        sf::Vector2f curPos = platforms_[i].GetPosition();
        float x1 = std::min(last.x, pos.x) - configDataPt_->squareSize.x;
        float y1 = std::min(last.y, pos.y) - configDataPt_->squareSize.y;
        float x2 = std::max(last.x, pos.x) + configDataPt_->squareSize.x;
        float y2 = std::max(last.y, pos.y) + configDataPt_->squareSize.y;

        if (x1 <= curPos.x && curPos.x <= x2 && y1 <= curPos.y && curPos.y <= y2)
            return true;
    }

    return false;
}

void Map::addBackground() {
    size_t sz = GetSize();
    Platform plat1 = platforms_[sz - 2]; 
    Platform plat2 = platforms_[sz - 1]; 
    sf::Vector2f pos1 = plat1.GetPosition();
    sf::Vector2f pos2 = plat2.GetPosition();
    Platform::Direction dir1 = plat1.GetDirection();
    Platform::Direction dir2 = plat2.GetDirection();

    float addW1 = (
        dir1 == Platform::Direction::Up || dir1 == Platform::Direction::Down
        ? configDataPt_->platformSize.x / 2 
        : configDataPt_->squareSize.x / 2
    );
    float addW2 = (
        dir2 == Platform::Direction::Up || dir2 == Platform::Direction::Down
        ? configDataPt_->platformSize.x / 2 
        : configDataPt_->squareSize.x / 2
    );
    float addH1 = (
        dir1 == Platform::Direction::Up || dir1 == Platform::Direction::Down 
        ? configDataPt_->squareSize.y / 2 
        : configDataPt_->platformSize.x / 2
    );
    float addH2 = (
        dir2 == Platform::Direction::Up || dir2 == Platform::Direction::Down 
        ? configDataPt_->squareSize.y / 2 
        : configDataPt_->platformSize.x / 2
    );

    float w = abs(pos1.x - pos2.x) + addW1 + addW2;;
    float h = abs(pos1.y - pos2.y) + addH1 + addH2;

    float X = std::min(pos1.x, pos2.x);
    float Y = std::min(pos1.y, pos2.y);
    X -= (pos1.x < pos2.x ? addW1 : addW2);
    Y -= (pos1.y < pos2.y ? addH1 : addH2);
    
    sf::RectangleShape back(sf::Vector2f(w, h));
    back.setPosition(X, Y);
    back.setFillColor(sf::Color::White); 
    sf::RectangleShape cover = back;
    back.setOutlineThickness(2.f);
    back.setOutlineColor(sf::Color::Black);

    background_.emplace_back(back);
    backgroundCover_.emplace_back(cover);
}

void Map::Render(sf::RenderWindow& window, const Camera& cam) {
    sf::Vector2f size = cam.GetSize();
    sf::Vector2f pos = cam.GetPosition();

    int x1 = (pos.x - size.x / 2) / chunkSize.x;
    int x2 = (pos.x + size.x / 2) / chunkSize.x;
    int y1 = (pos.y - size.y / 2) / chunkSize.y;
    int y2 = (pos.y + size.y / 2) / chunkSize.y;

    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            for (auto shape: gridMap1_[{x, y}])
                window.draw(shape);
        }
    }
    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            for (auto shape: gridMap2_[{x, y}])
                window.draw(shape);
        }
    }
}

void Map::Clear() {
    failed_ = false;
    platforms_.clear();
    background_.clear();
    backgroundCover_.clear();
    gridMap1_.clear();
    gridMap2_.clear();
    curPlatform = 0;
}

const std::vector<Platform>& Map::GetPlatforms() const {
    return platforms_;
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

std::vector<Platform::Direction> Map::getPossibleDirs(const sf::Vector2f speed) const {
    std::vector<Platform::Direction> ret;
    if (speed.x > 0) {
        ret.emplace_back(Platform::Direction::Right);
    }
    else {
        ret.emplace_back(Platform::Direction::Left);    
    }
    if (speed.y > 0) {
        ret.emplace_back(Platform::Direction::Down);    
    }
    else {
        ret.emplace_back(Platform::Direction::Up);
    }

    return ret;
}

size_t Map::GetSize() const {
    return platforms_.size();
}

const sf::Vector2f& Map::GetPositionRef() const {
    return centerPoint_;
}

bool Map::IsFailed() const {
    return failed_;
}

void Map::revert(std::unordered_map<int, int>& attempts, size_t& size) {
    int len = size / 3;
    while(len--) {
        attempts[size] = 0;
        platforms_.pop_back();
        background_.pop_back();
        backgroundCover_.pop_back();
        size--;
    }
}

sf::Vector2f Map::getAdaptedSpeed(float dt) const{
    sf::Vector2f speed = configDataPt_->speed;
    sf::Vector2f sqSz = configDataPt_->squareSize;
    sf::Vector2f dist = speed * dt;
    float k = 1.f;
    if (dist.x < sqSz.x || dist.y < sqSz.y) {
        float kx = sqSz.x / dist.x;
        float ky = sqSz.y / dist.y;
        k = std::max(kx, ky) + 0.1f;
    }

    speed *= k;
    return speed;
}


void rotatePoint(sf::Vector2f& point, const sf::Vector2f& center, float angle) {
    angle = angle * M_PI / 180.f;
    float x = cos(angle) * (point.x - center.x) - sin(angle) * (point.y - center.y);
    float y = sin(angle) * (point.x - center.x) + cos(angle) * (point.y - center.y);
    point.x = center.x + x;
    point.y = center.y + y;
}

std::pair<sf::Vector2f, sf::Vector2f> getBounds(const sf::RectangleShape& shape) {
    sf::Vector2f position = shape.getPosition();
    sf::Vector2f topLeft = shape.getPosition() - shape.getOrigin();
    std::cout << topLeft.x << ' ' << topLeft.y << '\n';
    sf::Vector2f bottomRight = topLeft + shape.getSize();
    float angle = shape.getRotation();
    rotatePoint(topLeft, position, angle);
    rotatePoint(bottomRight, position, angle);

    return {topLeft, bottomRight};
}

void Map::makeGridMap() {
    // for (size_t i = 0; i < platforms_.size(); ++i) {
    //     std::pair<sf::Vector2f, sf::Vector2f> bounds = getBounds(platforms_[i].GetRect());
    //     int x1 = bounds.first.x / chunkSize.x;
    //     int x2 = bounds.second.x / chunkSize.x;
    //     int y1 = bounds.first.y / chunkSize.y;
    //     int y2 = bounds.second.y / chunkSize.y;

    //     if (x1 > x2) std::swap(x1, x2);
    //     if (y1 > y2) std::swap(y1, y2);

    //     for (int x = x1; x <= x2; ++x) {
    //         for (int y = y1; y <= y2; ++y) {
    //             gridMap_[{x, y}].emplace_back(platforms_[i].GetRect());
    //         }
    //     }
    // }
    for (size_t i = 0; i < background_.size(); ++i) {
        std::pair<sf::Vector2f, sf::Vector2f> bounds = getBounds(background_[i]);
        int x1 = bounds.first.x / chunkSize.x;
        int x2 = bounds.second.x / chunkSize.x;
        int y1 = bounds.first.y / chunkSize.y;
        int y2 = bounds.second.y / chunkSize.y;

        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);

        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                gridMap1_[{x, y}].emplace_back(background_[i]);
            }
        }
    }
    for (size_t i = 0; i < backgroundCover_.size(); ++i) {
        std::pair<sf::Vector2f, sf::Vector2f> bounds = getBounds(backgroundCover_[i]);
        int x1 = bounds.first.x / chunkSize.x;
        int x2 = bounds.second.x / chunkSize.x;
        int y1 = bounds.first.y / chunkSize.y;
        int y2 = bounds.second.y / chunkSize.y;

        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);

        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                gridMap2_[{x, y}].emplace_back(backgroundCover_[i]);
            }
        }
    }
}

