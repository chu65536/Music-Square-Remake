#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "conductor.hpp"

class Game {
public:
    Game();
    void Run();
private:
    void handleGlobalEvents();
    void updateState(State::Type);
    sf::RenderWindow window_;
    std::unique_ptr<State> currentState_;
};