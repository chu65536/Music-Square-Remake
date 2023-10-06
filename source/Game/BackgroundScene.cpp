#include "Game/BackgroundScene.hpp"


// Scene
void BackgroundScene::Init(const SettingsData& settingsData) {
    m_settingsDataPt = &settingsData;
    m_square.Init(settingsData);
    m_background.Init(settingsData);
}

void BackgroundScene::Update(const sf::Time& time) {
    m_background.Update();
    m_square.Update(time, sf::Vector2f(m_settingsDataPt->windowSize));
}

void BackgroundScene::Render(sf::RenderWindow& window) {
    m_background.Render(window);
    m_square.Render(window);
}


// Square
void DemoSquare::Init(const SettingsData& settingsData) {
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

void DemoSquare::Update(const sf::Time& dt, const sf::Vector2f& windowSize) {
    m_position.x += m_speedPt->x * dir.x * dt.asSeconds();
    m_position.y += m_speedPt->y * dir.y * dt.asSeconds();
    m_rect.setOrigin(*m_sizePt / 2.f);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(*m_colorPt);
    m_rect.setSize(*m_sizePt);
    m_rect.setOutlineThickness(*m_outlineThicknessPt);
    m_rect.setOutlineColor(*m_outlineColorPt);
    if (m_position.y + m_sizePt->y / 2.f >= windowSize.y) {
        dir.y = -1;
    }
    if (m_position.x + m_sizePt->x / 2.f >= windowSize.x) {
        dir.x = -1;
    }
    if (m_position.y - m_sizePt->y / 2.f <= 0.f) {
        dir.y = 1;
    }
    if (m_position.x - m_sizePt->x / 2.f <= windowSize.x / 3.f) {
        dir.x = 1;
    }
}

void DemoSquare::Render(sf::RenderWindow& window) {
    window.draw(m_rect);
}

// Background
void DemoBackground::Init(const SettingsData& settingsData) {
    sf::Vector2f windowSz = sf::Vector2f(settingsData.windowSize);
    m_size = sf::Vector2f(windowSz.x / 3.f * 2.f, windowSz.y);
    m_position = sf::Vector2f(windowSz.x / 3.f, 0.f);
    m_colorPt = &settingsData.backgroundColor;
    m_rect.setSize(m_size);
    m_rect.setPosition(m_position);
    m_rect.setFillColor(*m_colorPt);
}

void DemoBackground::Update() {
    m_rect.setFillColor(*m_colorPt);
}

void DemoBackground::Render(sf::RenderWindow& window) {
    window.draw(m_rect);
}

sf::Vector2f DemoBackground::GetSize() const {
    return m_size;
}
 