#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Data/SettingsData.hpp"


class DemoSquare {
public:
    void Init(const SettingsData& settingsData);
    void Render(sf::RenderWindow& window);
    void Update(const sf::Time& dt, const sf::Vector2f& windowSize, float wallsSize);
private:
    sf::Vector2f m_position;
    const sf::Vector2f* m_sizePt;
    const sf::Vector2f* m_speedPt;
    const sf::Color* m_colorPt;
    const float* m_outlineThicknessPt;
    const sf::Color* m_outlineColorPt; 
    sf::Vector2f dir;
    sf::RectangleShape m_rect;
};

class DemoBackground {
public:
    void Init(const SettingsData& settingsData, float wallsSize);
    void Update();
    void Render(sf::RenderWindow& window); 
    sf::Vector2f GetSize() const;
private:
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    const sf::Color* m_colorPt;
    sf::RectangleShape m_rect;
    const sf::Color* m_outlineColorPt;
    const float* m_outlineThickness;
};

class BackgroundScene {
public:
    void Init(const SettingsData& settingsData);
    void Update(const sf::Time& dt);
    void Render(sf::RenderWindow& window);
private:
    DemoSquare m_square;
    DemoBackground m_background;
    float m_wallsSize;
    const SettingsData* m_settingsDataPt;
};