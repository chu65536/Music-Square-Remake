#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_set>
#include <Tools/Math.hpp>
#include "Game/Map.hpp"
#include "Data/GameData.hpp"
#include "Tools/Debug.hpp"


void Map::Init(const SettingsData* settingsData, const SongData* songData) {
    m_dataPt = settingsData;
    m_SongDataPt = songData;
    makePlatforms();
}

void Map::makePlatforms() {
    DEBUG_TIMER_START();
    makeFirstPlatform();
    std::unordered_map<unsigned, unsigned> attempts;
    bool remakeLastPlatform = false;
    while (m_platforms.size() != m_SongDataPt->delays.size()) {
        DEBUG_LOG(std::to_string(float(m_platforms.size()) / m_SongDataPt->delays.size() * 100));
        handleAttempts(attempts);
        sf::Vector2f nextPosition = getNextPosition();
        Platform nextPlatform = makeNextPlatform(nextPosition, remakeLastPlatform);
        if (checkCollisions(nextPlatform)) {
            if (!goBack()) {
                Debug::Timer::Stop("Map generation failed");
                return; 
            }
            remakeLastPlatform = true;
            continue;
        }
        addNextPlatform(nextPlatform);
    } 
    makeGridMap();
    DEBUG_TIMER_STOP("Map generated");
}

void Map::makeFirstPlatform() {
    sf::Vector2f position (0.f, 0.f);
    sf::Vector2f speed = m_dataPt->squareSpeed;
    speed.x *= (rand() % 2 ? -1: 1);
    speed.y *= (rand() % 2 ? -1: 1);
    std::vector<Platform::Direction> directions = getPossibleDirections(speed);

    Platform::Data platformData;
    platformData.position = position;
    platformData.time = m_SongDataPt->delays[0];
    platformData.directions = directions;
    platformData.color = m_dataPt->wallsColor;
    platformData.size = m_dataPt->platformSize;
    platformData.squareSize = m_dataPt->squareSize;
    platformData.speedBefore = speed;
    m_platforms.emplace_back(std::move(platformData));
}

void Map::handleAttempts(std::unordered_map<unsigned, unsigned>& attempts) {
    attempts[m_platforms.size()]++;
    if (attempts[m_platforms.size()] > 100) {
        revert(attempts);
    }
}

sf::Vector2f Map::getNextPosition() {
    float deltaTime = m_SongDataPt->delays[m_platforms.size()] - m_SongDataPt->delays[m_platforms.size() - 1]; 
    sf::Vector2f adaptedSpeed = getAdaptedSpeed(deltaTime);
    m_platforms[m_platforms.size() - 1].AdaptSpeedAfter(adaptedSpeed);
    sf::Vector2f speed = m_platforms[m_platforms.size() - 1].GetSpeedAfter(); 
    sf::Vector2f prevPos = m_platforms[m_platforms.size() - 1].GetPosition();
    sf::Vector2f newPos = prevPos + speed * deltaTime;

    return newPos;
}

Platform Map::makeNextPlatform(const sf::Vector2f& position, bool& remakeLastPlatform) {
    if (remakeLastPlatform) {
        Platform ret = m_platforms[m_platforms.size() - 1];
        m_platforms.pop_back();
        m_background.pop_back();
        m_backgroundCover.pop_back();
        remakeLastPlatform = false;
        return ret;
    }

    sf::Vector2f speed = m_platforms[m_platforms.size() - 1].GetSpeedAfter();
    std::vector<Platform::Direction> possibleDirections = getPossibleDirections(speed);

    Platform::Data platformData;
    platformData.position = position;
    platformData.directions = possibleDirections;
    platformData.color = m_dataPt->wallsColor;
    platformData.speedBefore = speed;
    platformData.squareSize = m_dataPt->squareSize;
    platformData.size = m_dataPt->platformSize;
    platformData.time = m_SongDataPt->delays[m_platforms.size()];
    Platform ret(std::move(platformData));
    return ret;
}

bool Map::checkCollisions(const Platform& platform) {
    sf::FloatRect rect1 = platform.GetRect().getGlobalBounds();
    for (size_t i = 0; i < m_platforms.size(); ++i) {
        sf::FloatRect rect2 = m_platforms[i].GetRect().getGlobalBounds();
        if (rect1.intersects(rect2)) {
            return true;
        }
    }

    for (size_t i = 0; i < m_background.size(); ++i) {
        sf::FloatRect rect2 = m_background[i].getGlobalBounds();
        if (rect1.intersects(rect2)) {
            return true;
        }
    }

    sf::RectangleShape path = makeRectangle(m_platforms[m_platforms.size() - 1], platform);
    sf::FloatRect pathRect = path.getGlobalBounds();
    for (size_t i = 0; i < m_platforms.size() - 1; ++i) {
        sf::FloatRect rect2 = m_platforms[i].GetRect().getGlobalBounds();
        if (pathRect.intersects(rect2)) {
            return true;
        }
    }
    return false; 
}

void Map::addNextPlatform(const Platform& platform) {
    m_platforms.emplace_back(platform);
    addBackground();
}

void Map::addBackground() {
    sf::RectangleShape back = makeRectangle(m_platforms[m_platforms.size() - 1], m_platforms[m_platforms.size() - 2]);
    back.setFillColor(m_dataPt->backgroundColor); 
    sf::RectangleShape cover = back;
    back.setOutlineThickness(m_dataPt->wallsOutlineThickness);
    back.setOutlineColor(m_dataPt->wallsOutlineColor);

    m_background.emplace_back(back);
    m_backgroundCover.emplace_back(cover);
}

void Map::Render(sf::RenderWindow& window, const Camera& cam) {
    sf::Vector2f size = cam.GetSize();
    sf::Vector2f pos = cam.GetPosition();

    int x1 = (pos.x - size.x / 2) / m_dataPt->chunkSize.x;
    int x2 = (pos.x + size.x / 2) / m_dataPt->chunkSize.x;
    int y1 = (pos.y - size.y / 2) / m_dataPt->chunkSize.y;
    int y2 = (pos.y + size.y / 2) / m_dataPt->chunkSize.y;

    std::unordered_set<Platform*> renderPool;
    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            for (auto object: m_gridMap[{x, y}]) {
                auto val = *object;
                renderPool.insert(object);
            }
        }
    }
    for (auto obj: renderPool) {
        obj->Render(window);
    }
    for (auto back: m_background) {
        window.draw(back);
    }
    for (auto cover: m_backgroundCover) {
        window.draw(cover);
    }
}

void Map::Clear() {
    m_failed = false;
    m_platforms.clear();
    m_background.clear();
    m_backgroundCover.clear();
    m_gridMap.clear();
    m_curPlatform = 0;
}

const std::vector<Platform>& Map::GetPlatforms() const {
    return m_platforms;
}


Platform& Map::GetNextPlatform(float time) {
    while (m_curPlatform + 1 < m_platforms.size() && time > m_platforms[m_curPlatform + 1].GetTime()) {
        m_curPlatform++;
    }
    return m_platforms[m_curPlatform];
}



bool Map::isEnd() const {
    return m_platforms.size() - 1 == m_curPlatform;
}

std::vector<Platform::Direction> Map::getPossibleDirections(const sf::Vector2f speed) const {
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
    return m_platforms.size();
}

bool Map::IsFailed() const {
    return m_failed;
}

void Map::revert(std::unordered_map<unsigned, unsigned>& attempts) {
    attempts.clear();
    int len = m_platforms.size() / 3;
    while(len--) {
        m_platforms.pop_back();
        m_background.pop_back();
        m_backgroundCover.pop_back();
    }
}

sf::Vector2f Map::getAdaptedSpeed(float dt) const{
    sf::Vector2f speed = m_dataPt->squareSpeed;
    sf::Vector2f sqSz = m_dataPt->squareSize;
    sf::Vector2f plSz = m_dataPt->platformSize;
    float sz = std::max(std::max(sqSz.x, plSz.x), std::max(sqSz.y, plSz.x));
    sf::Vector2f dist = speed * dt;
    float k = 1.f;
    float kx = sz / dist.x;
    float ky = sz / dist.y;
    k = std::max(k, kx * 1.5f);
    k = std::max(k, ky * 1.5f);
    speed *= k;
    return speed;
}

bool Map::goBack() {
    while(m_platforms.size() != 1 && !m_platforms[m_platforms.size() - 1].TryAnotherDirection()) {
        m_platforms.pop_back();
        m_background.pop_back();
        m_backgroundCover.pop_back();
    }
    if (m_platforms.size() == 1) {
        return false;
    }
    return true;
}

void Map::makeGridMap() {
    for (size_t i = 0; i < m_platforms.size(); ++i) {
        std::vector<sf::Vector2f> bounds = m_platforms[i].GetBounds();
        float x1, x2, y1, y2;
        x1 = x2 = bounds[0].x;
        y1 = y2 = bounds[0].y;
        for (size_t j = 0; j < bounds.size(); ++j) {
            x1 = std::min(x1, bounds[j].x);
            x2 = std::max(x2, bounds[j].x);
            y1 = std::min(y1, bounds[j].y);
            y2 = std::max(y2, bounds[j].y);
        }
        int l = x1 / m_dataPt->chunkSize.x;
        int r = x2 / m_dataPt->chunkSize.x;
        int u = y1 / m_dataPt->chunkSize.y;
        int d = y2 / m_dataPt->chunkSize.y;
        for (int x = l; x <= r; ++x) {
            for (int y = u; y <= d; ++y) {
                m_gridMap[{x, y}].emplace_back(&m_platforms[i]);
            }
        }
    }
}

sf::RectangleShape Map::makeRectangle(const Platform& platform1, const Platform& platform2) {
    size_t sz = GetSize();
    sf::Vector2f pos1 = platform1.GetPosition();
    sf::Vector2f pos2 = platform2.GetPosition();
    Platform::Direction dir1 = platform1.GetDirection();
    Platform::Direction dir2 = platform2.GetDirection();
    sf::Vector2f squareSize = m_dataPt->squareSize;
    sf::Vector2f platformSize = m_dataPt->platformSize;
    sf::Vector2f size (std::max(squareSize.x, platformSize.x), std::max(squareSize.y, platformSize.x));

    float addW1 = (
        dir1 == Platform::Direction::Up || dir1 == Platform::Direction::Down
        ? size.x / 2 
        : m_dataPt->squareSize.x / 2
    );
    float addW2 = (
        dir2 == Platform::Direction::Up || dir2 == Platform::Direction::Down
        ? size.x / 2 
        : m_dataPt->squareSize.x / 2
    );
    float addH1 = (
        dir1 == Platform::Direction::Up || dir1 == Platform::Direction::Down 
        ? m_dataPt->squareSize.y / 2 
        : size.y / 2
    );
    float addH2 = (
        dir2 == Platform::Direction::Up || dir2 == Platform::Direction::Down 
        ? m_dataPt->squareSize.y / 2 
        : size.y / 2
    );

    float w = abs(pos1.x - pos2.x) + addW1 + addW2;;
    float h = abs(pos1.y - pos2.y) + addH1 + addH2;

    float X = std::min(pos1.x, pos2.x);
    float Y = std::min(pos1.y, pos2.y);
    X -= (pos1.x < pos2.x ? addW1 : addW2);
    Y -= (pos1.y < pos2.y ? addH1 : addH2);
    
    sf::RectangleShape rect(sf::Vector2f(w, h));
    rect.setPosition(X, Y);
    return rect;
}



