#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Data/SettingsData.hpp"


class BackgroundScene {
public:
    void Init(const SettingsData& settingsData);
    void Update(const sf::Time& dt);
    void Render(sf::RenderWindow& window);
private:
    void updateSquare(const sf::Vector2f& speed, float dt);
    sf::RectangleShape m_square;
    sf::Vector2f m_squareSize;
    sf::RectangleShape m_background;
    sf::Vector2f m_backgroundSize;
    const SettingsData* m_settingsDataPt;
    sf::Vector2f m_squarePosition;
    sf::Vector2i m_dir;
};