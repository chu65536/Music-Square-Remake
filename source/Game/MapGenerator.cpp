#include "Game/MapGenerator.hpp"
#include "Tools/Math.hpp"


MapGenerator::MapGenerator(const SettingsData& settingsData):
    m_settingsData(settingsData)
{
}

bool MapGenerator::Generate(const SongData::Track& trackData, const sf::Vector2f& startPoint) 
{   
    m_startPoint = startPoint;
    m_trackData = &trackData;

    makeFirstPlatform();
    std::unordered_map<int, int> attempts;
    bool remakeLastPlatform = false;
    while (m_platforms.size() != m_trackData->delays.size()) 
    {
        handleAttempts(attempts);
        sf::Vector2f nextPosition = getNextPosition();
        Platform nextPlatform = makeNextPlatform(nextPosition, remakeLastPlatform);
        if (checkCollisions(nextPlatform)) 
        {
            if (!goBack()) 
            {
                return false; 
            }
            remakeLastPlatform = true;
            continue;
        }
        m_platforms.emplace_back(nextPlatform);
        addBackground();
    } 
    makeWalls();
    makeGridMap();
    
    return true;
}

bool MapGenerator::Generate(const ParsedMapData::Track& parsedTrackData)
{
    m_platforms = std::move(parsedTrackData.platforms);
    makeBackgroundByPlatforms();
    makeWalls();
    makeGridMap();

    return true;
}

void MapGenerator::makeFirstPlatform() 
{
    sf::Vector2f speed = m_settingsData.squareSpeed;
    speed.x *= (rand() % 2 ? -1: 1);
    speed.y *= (rand() % 2 ? -1: 1);
    std::vector<Platform::Direction> directions = getPossibleDirections(speed);

    Platform::Data platformData;
    platformData.position = m_startPoint;
    platformData.time = m_trackData->delays[0];
    platformData.directions = directions;
    platformData.color = m_settingsData.platformColor;
    platformData.outlineColor = m_settingsData.platformOutlineColor;
    platformData.outlineThickness = m_settingsData.platformOutlineThickness;
    platformData.size = m_settingsData.platformSize;
    platformData.squareSize = m_settingsData.squareSize;
    platformData.speedBefore = speed;
    platformData.speedAfter = speed;

    m_platforms.emplace_back(std::move(platformData));
}

void MapGenerator::handleAttempts(std::unordered_map<int, int>& attempts)
{
    attempts[m_platforms.size()]++;
    if (attempts[m_platforms.size()] > 100) 
    {
        attempts.clear();
        int len = m_platforms.size() / 3;
        while(len--) 
        {
            m_platforms.pop_back();
            m_background.pop_back();
            m_backgroundCover.pop_back();
        }
    }
}

sf::Vector2f MapGenerator::getNextPosition() 
{
    float deltaTime = m_trackData->delays[m_platforms.size()] - m_trackData->delays[m_platforms.size() - 1]; 
    sf::Vector2f adaptedSpeed = getAdaptedSpeed(deltaTime);
    m_platforms[m_platforms.size() - 1].AdaptSpeedAfter(adaptedSpeed);
    sf::Vector2f speed = m_platforms[m_platforms.size() - 1].GetSpeedAfter(); 
    sf::Vector2f prevPos = m_platforms[m_platforms.size() - 1].GetPosition();
    sf::Vector2f newPos = prevPos + speed * deltaTime;

    return newPos;
}

Platform MapGenerator::makeNextPlatform(const sf::Vector2f& position, bool& remakeLastPlatform) 
{
    if (remakeLastPlatform) 
    {
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
    platformData.color = m_settingsData.platformColor;
    platformData.outlineColor = m_settingsData.platformOutlineColor;
    platformData.outlineThickness = m_settingsData.platformOutlineThickness;
    platformData.speedBefore = speed;
    platformData.speedAfter = speed;
    platformData.squareSize = m_settingsData.squareSize;
    platformData.size = m_settingsData.platformSize;
    platformData.time = m_trackData->delays[m_platforms.size()];
    Platform ret(std::move(platformData));
    return ret;
}

bool MapGenerator::checkCollisions(const Platform& platform) 
{
    sf::FloatRect rect1 = platform.GetRect().getGlobalBounds();
    for (size_t i = 0; i < m_platforms.size(); ++i) 
    {
        sf::FloatRect rect2 = m_platforms[i].GetRect().getGlobalBounds();
        if (rect1.intersects(rect2)) 
        {
            return true;
        }
    }

    for (size_t i = 0; i < m_background.size(); ++i) 
    {
        sf::FloatRect rect2 = m_background[i].getGlobalBounds();
        if (rect1.intersects(rect2)) 
        {
            return true;
        }
    }

    sf::RectangleShape path = makeRectangle(m_platforms[m_platforms.size() - 1], platform);
    sf::FloatRect pathRect = path.getGlobalBounds();
    for (size_t i = 0; i < m_platforms.size() - 1; ++i) 
    {
        sf::FloatRect rect2 = m_platforms[i].GetRect().getGlobalBounds();
        if (pathRect.intersects(rect2)) 
        {
            return true;
        }
    }
    return false; 
}

void MapGenerator::addBackground() {
    sf::RectangleShape back = makeRectangle(m_platforms[m_platforms.size() - 1], m_platforms[m_platforms.size() - 2]);
    back.setFillColor(m_settingsData.backgroundColor); 
    sf::RectangleShape cover = back;
    back.setOutlineThickness(m_settingsData.wallsOutlineThickness);
    back.setOutlineColor(m_settingsData.wallsOutlineColor);

    m_background.emplace_back(back);
    m_backgroundCover.emplace_back(cover);
}

std::vector<Platform::Direction> MapGenerator::getPossibleDirections(const sf::Vector2f speed) const 
{
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

sf::Vector2f MapGenerator::getAdaptedSpeed(float dt) const
{
    sf::Vector2f speed = m_settingsData.squareSpeed;
    sf::Vector2f sqSz = m_settingsData.squareSize;
    sf::Vector2f plSz = m_settingsData.platformSize;
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

bool MapGenerator::goBack() 
{
    while(m_platforms.size() != 1 && !m_platforms[m_platforms.size() - 1].TryAnotherDirection()) 
    {
        m_platforms.pop_back();
        m_background.pop_back();
        m_backgroundCover.pop_back();
    }
    if (m_platforms.size() == 1) 
    {
        return false;
    }
    return true;
}

sf::RectangleShape MapGenerator::makeRectangle(const Platform& platform1, const Platform& platform2) 
{
    size_t sz = m_platforms.size();
    sf::Vector2f pos1 = platform1.GetPosition();
    sf::Vector2f pos2 = platform2.GetPosition();
    Platform::Direction dir1 = platform1.GetDirection();
    Platform::Direction dir2 = platform2.GetDirection();
    sf::Vector2f squareSize = m_settingsData.squareSize;
    sf::Vector2f platformSize = m_settingsData.platformSize;
    sf::Vector2f size (std::max(squareSize.x, platformSize.x), std::max(squareSize.y, platformSize.x));

    float addW1 = (
        dir1 == Platform::Direction::Up || dir1 == Platform::Direction::Down
        ? size.x / 2 
        : m_settingsData.squareSize.x / 2
    );
    float addW2 = (
        dir2 == Platform::Direction::Up || dir2 == Platform::Direction::Down
        ? size.x / 2 
        : m_settingsData.squareSize.x / 2
    );
    float addH1 = (
        dir1 == Platform::Direction::Up || dir1 == Platform::Direction::Down 
        ? m_settingsData.squareSize.y / 2 
        : size.y / 2
    );
    float addH2 = (
        dir2 == Platform::Direction::Up || dir2 == Platform::Direction::Down 
        ? m_settingsData.squareSize.y / 2 
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

void MapGenerator::makeWalls()
{
    float l, r, u, d;
    l = r = m_startPoint.x;
    u = d = m_startPoint.y;

    for (auto& platform: m_platforms)
    {
        float x = platform.GetPosition().x;
        float y = platform.GetPosition().y;

        l = std::min(l, x); r = std::max(r, x);
        u = std::min(u, y); d = std::max(d, y);
    }

    float w = r - l + m_settingsData.windowSize.x;
    float h = d - u + m_settingsData.windowSize.y;
    m_wallsRect = sf::RectangleShape({w, h});
    m_wallsRect.setOrigin(w * 0.5f, h * 0.5f);
    m_wallsRect.setPosition({(l + r) * 0.5f, (u + d) * 0.5f});
    m_wallsRect.setFillColor(m_settingsData.wallsColor);
}

void MapGenerator::makeGridMap() 
{
    std::vector<sf::RectangleShape> platformRects;
    if (m_settingsData.visiblePlatforms)
    {
        for (auto& platform: m_platforms)
        {
            platformRects.emplace_back(platform.GetRect());
        }
        m_gridMaps.emplace_back(calcGridMap(platformRects));
    }
    m_gridMaps.emplace_back(calcGridMap(m_background));
    m_gridMaps.emplace_back(calcGridMap(m_backgroundCover));
}

GridMap MapGenerator::calcGridMap(std::vector<sf::RectangleShape>& rects)
{
    GridMap res;
    for (auto& rect: rects) 
    {
        std::vector<sf::Vector2f> bounds = Math::GetBounds(rect);
        float x1, x2, y1, y2;
        x1 = x2 = bounds[0].x;
        y1 = y2 = bounds[0].y;

        for (size_t j = 0; j < bounds.size(); ++j) 
        {
            x1 = std::min(x1, bounds[j].x);
            x2 = std::max(x2, bounds[j].x);
            y1 = std::min(y1, bounds[j].y);
            y2 = std::max(y2, bounds[j].y);
        }

        int l = x1 / m_settingsData.chunkSize.x;
        int r = x2 / m_settingsData.chunkSize.x;
        int u = y1 / m_settingsData.chunkSize.y;
        int d = y2 / m_settingsData.chunkSize.y;
        for (int x = l; x <= r; ++x) 
        {
            for (int y = u; y <= d; ++y) 
            {
                res[{x, y}].emplace_back(rect);    
            }
        }
    }
    return res;
}

MapData&& MapGenerator::MoveData()
{
    m_data.platforms = std::move(m_platforms);
    m_data.background = std::move(m_background);
    m_data.backgroundCover = std::move(m_backgroundCover);
    m_data.wallsRect = std::move(m_wallsRect);
    m_data.gridMaps = std::move(m_gridMaps);

    return std::move(m_data);
}

void MapGenerator::Export(std::ofstream& file)
{      
    file << "#platforms" << '\n';
    for (auto& platform: m_platforms)
    {
        platform.Export(file);
    }
}

void MapGenerator::makeBackgroundByPlatforms()
{
    for (int i = 1; i < m_platforms.size(); ++i)
    {
        sf::RectangleShape back = makeRectangle(m_platforms[i - 1], m_platforms[i]);
        back.setFillColor(m_settingsData.backgroundColor); 
        sf::RectangleShape cover = back;
        back.setOutlineThickness(m_settingsData.wallsOutlineThickness);
        back.setOutlineColor(m_settingsData.wallsOutlineColor);

        m_background.emplace_back(back);
        m_backgroundCover.emplace_back(cover);
    }
}