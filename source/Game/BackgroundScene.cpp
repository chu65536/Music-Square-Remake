#include "Game/BackgroundScene.hpp"

// Scene
void BackgroundScene::Init(const SettingsData& settingsData) 
{
    m_settingsDataPt = &settingsData;
    m_wallsSize = settingsData.windowSize.y / 8.f;
    m_square.Init(settingsData);
    m_background.Init(settingsData, m_wallsSize);
    m_platform.Init(settingsData);
}

void BackgroundScene::Update(const sf::Time& time) 
{
    m_background.Update();
    m_square.Update(time, sf::Vector2f(m_settingsDataPt->windowSize), m_wallsSize);
    m_platform.Update();
    m_wallsSize = m_settingsDataPt->windowSize.y / 8.f;
}

void BackgroundScene::Render(sf::RenderWindow& window) 
{
    m_background.Render(window);
    m_square.Render(window);
    if (m_settingsDataPt->visiblePlatforms)
    {
        m_platform.Render(window);
    }
}

// Square
void DemoSquare::Init(const SettingsData& settingsData) 
{
    sf::Vector2f windowSz = sf::Vector2f(settingsData.windowSize);
    m_sizePt = &settingsData.squareSize;
    m_position = sf::Vector2f(windowSz.x / 3.f + m_sizePt->x / 2.f, windowSz.y / 2.f);
    m_speedPt = &settingsData.squareSpeed;
    m_colorPt = &settingsData.squareColor;
    m_outlineThicknessPt = &settingsData.squareOutlineThickness;
    m_outlineColorPt = &settingsData.squareOutlineColor;
    m_rect.setOrigin(settingsData.squareSize / 2.f);
    m_rect.setPosition(m_position);
    m_rect.setSize(*m_sizePt);
    m_rect.setFillColor(*m_colorPt);
    m_rect.setOutlineThickness(*m_outlineThicknessPt);
    m_rect.setOutlineColor(*m_outlineColorPt);

    dir = sf::Vector2f(1, 1);
}

void DemoSquare::Update(const sf::Time& dt, const sf::Vector2f& windowSize, float wallsSize) 
{
    m_position.x += m_speedPt->x * dir.x * dt.asSeconds();
    m_position.y += m_speedPt->y * dir.y * dt.asSeconds();
    m_rect.setOrigin(*m_sizePt / 2.f);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(*m_colorPt);
    m_rect.setSize(*m_sizePt);
    m_rect.setOutlineThickness(*m_outlineThicknessPt);
    m_rect.setOutlineColor(*m_outlineColorPt);
    if (m_position.y + m_sizePt->y / 2.f >= windowSize.y - wallsSize) {
        dir.y = -1;
    }
    if (m_position.x + m_sizePt->x / 2.f >= windowSize.x) {
        dir.x = -1;
    }
    if (m_position.y - m_sizePt->y / 2.f <= wallsSize) {
        dir.y = 1;
    }
    if (m_position.x - m_sizePt->x / 2.f <= windowSize.x / 3.f) {
        dir.x = 1;
    }
}

void DemoSquare::Render(sf::RenderWindow& window) 
{
    window.draw(m_rect);
}

// Background
void DemoBackground::Init(const SettingsData& settingsData, float wallsSize) 
{
    sf::Vector2f windowSz = sf::Vector2f(settingsData.windowSize);
    m_size = sf::Vector2f(windowSz.x / 3.f * 2.f, windowSz.y - wallsSize * 2);
    m_position = sf::Vector2f(windowSz.x / 3.f, wallsSize);
    m_colorPt = &settingsData.backgroundColor;
    m_outlineColorPt = &settingsData.wallsOutlineColor;
    m_outlineThicknessPt = &settingsData.wallsOutlineThickness;
    m_rect.setSize(m_size);
    m_rect.setPosition(m_position);
}

void DemoBackground::Update() 
{
    m_rect.setFillColor(*m_colorPt);
    m_rect.setOutlineColor(*m_outlineColorPt);
    m_rect.setOutlineThickness(*m_outlineThicknessPt);
}

void DemoBackground::Render(sf::RenderWindow& window) 
{
    window.draw(m_rect);
}

sf::Vector2f DemoBackground::GetSize() const 
{
    return m_size;
}

// Platform
void DemoPlatform::Init(const SettingsData& settingsData)
{
    sf::Vector2f windowSz = sf::Vector2f(settingsData.windowSize);
    m_sizePt = &settingsData.platformSize;
    m_position = sf::Vector2f(windowSz.x / 3.f * 2.f, windowSz.y / 8.f * 7.f + m_sizePt->y * 0.5f);
    m_colorPt = &settingsData.platformColor;
    m_outlineThicknessPt = &settingsData.platformOutlineThickness;
    m_outlineColorPt = &settingsData.platformOutlineColor;
    m_rect.setOrigin(settingsData.platformSize / 2.f);
    m_rect.setPosition(m_position);
    m_rect.setSize(*m_sizePt);
    m_rect.setFillColor(*m_colorPt);
    m_rect.setOutlineThickness(*m_outlineThicknessPt);
    m_rect.setOutlineColor(*m_outlineColorPt);
}

void DemoPlatform::Update()
{
    m_position.y += (m_sizePt->y - m_rect.getSize().y) * 0.5f;
    m_rect.setOrigin(*m_sizePt / 2.f);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(*m_colorPt);
    m_rect.setSize(*m_sizePt);
    m_rect.setOutlineThickness(*m_outlineThicknessPt);
    m_rect.setOutlineColor(*m_outlineColorPt);   
}

void DemoPlatform::Render(sf::RenderWindow& window)
{
    window.draw(m_rect);
}