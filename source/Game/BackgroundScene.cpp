#include "Game/BackgroundScene.hpp"


void BackgroundScene::Init(const SettingsData& settingsData) {
    m_settingsDataPt = &settingsData;
    m_backgroundSize = sf::Vector2f(500.f, 500.f);
    m_background.setSize(m_backgroundSize);
    m_background.setOrigin(m_backgroundSize / 2.f);
    m_squarePosition.x = -m_backgroundSize.x / 2 + m_settingsDataPt->squareSize.x / 2;
    m_squarePosition.y = 0.f;
    m_dir = sf::Vector2i(1, 1);
    m_squareSize = m_settingsDataPt->squareSize;
}

void BackgroundScene::Update(const sf::Time& time) {
    m_squareSize = m_settingsDataPt->squareSize;
    m_square.setSize(m_settingsDataPt->squareSize);
    m_square.setOrigin(m_settingsDataPt->squareSize / 2.f);
    m_square.setFillColor(m_settingsDataPt->squareColor);
    m_background.setFillColor(m_settingsDataPt->backgroundColor);
    updateSquare(m_settingsDataPt->squareSpeed, time.asSeconds());
}

void BackgroundScene::Render(sf::RenderWindow& window) {
    window.draw(m_background);
    window.draw(m_square);
}

void BackgroundScene::updateSquare(const sf::Vector2f& speed, float dt) {
    if (m_squarePosition.x + m_squareSize.x / 2 >= m_backgroundSize.x / 2) {
        m_dir.x = -1; 
    }
    if (m_squarePosition.x - m_squareSize.x / 2 <= -m_backgroundSize.x / 2) {
        m_dir.x = 1; 
    }
    if (m_squarePosition.y + m_squareSize.y / 2 >= m_backgroundSize.y / 2) {
        m_dir.y = -1;
    }
    if (m_squarePosition.y - m_squareSize.y / 2 <= -m_backgroundSize.y / 2) {
        m_dir.y = 1;
    }
    m_squarePosition.x += speed.x * m_dir.x * dt;
    m_squarePosition.y += speed.y * m_dir.y * dt;
    m_square.setPosition(m_squarePosition);
}   