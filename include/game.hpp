#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "state.hpp"
#include "gamedata.hpp"
#include "configdata.hpp"


class Game {
public:
    Game();
    void Run();
private:
    void handleGlobalEvents();
    void setState(State::Type type);
    sf::RenderWindow window_;
    std::unique_ptr<State> currentState_;
    GameData gameData_;
    ConfigData configData_;
};