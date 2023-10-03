#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "States/State.hpp"
#include "Data/GameData.hpp"
#include "Data/SettingsData.hpp"
#include "Data/InterfaceData.hpp"
#include "Game/BackgroundScene.hpp"


class Game {
public:
    Game();
    void Run();
private:
    void update();
    void render();
    void handleEvents();
    void setState(State::Type type);
    void debugWindow(const sf::Time& dt) const;
    void initImGui();

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    std::unique_ptr<State> m_currentState;
    State::Type m_currentStateType;
    GameData m_gameData;
    SettingsData m_settingsData;
    InterfaceData m_interfaceData;
    BackgroundScene m_backgroundScene;
};