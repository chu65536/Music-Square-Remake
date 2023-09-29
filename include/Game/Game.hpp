#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "States/State.hpp"
#include "Data/GameData.hpp"


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

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    std::unique_ptr<State> m_currentState;
    GameData m_gameData;
};