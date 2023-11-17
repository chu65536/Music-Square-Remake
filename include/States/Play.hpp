#pragma once

#include "States/State.hpp"
#include "Game/Conductor.hpp"
#include "Data/GameData.hpp"
#include "Data/SettingsData.hpp"
#include "Game/Map.hpp"
#include "Game/Square.hpp"
#include "Game/Camera.hpp"
#include <deque>


struct Viewport
{
    sf::FloatRect rect;
    int id;
};

class Play : public State 
{
public:
    Play(GameData& gameData, const SettingsData& settingsData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    void drawBackground(sf::RenderWindow& window);
    void addScreen(GameData::Screen* screen);
    void removeScreen(int id);
    void addViewport(int id);
    void removeViewport(int id);
    sf::FloatRect& getViewportByID(int id);

    GameData& m_gameData;
    const SettingsData& m_settingsData;
    Conductor m_conductor;
    float m_timer = 0.f;
    bool m_exit = false;
    std::deque<Viewport> m_viewports;
    std::vector<GameData::Screen*> m_activeScreens;
};