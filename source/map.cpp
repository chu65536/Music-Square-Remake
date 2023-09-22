#include <iostream>
#include <chrono>
#include <thread>
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
    
    background_.emplace_back(back);
}

void Map::Render(sf::RenderWindow& window) const {
    for (size_t i = 0; i < background_.size(); ++i) {
        window.draw(background_[i]);
    } 
    // for (size_t i = 0; i < platforms_.size(); ++i) {
    //     window.draw(platforms_[i].GetRect());
    // } 
}

void Map::Clear() {
    failed_ = false;
    platforms_.clear();
    background_.clear();
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

