#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "state.hpp"
#include "conductor.hpp"
#include "menuplaydata.hpp"


class Game {
public:
    Game();
    void Run();
private:
    void handleGlobalEvents();
    void updateState(State::Type);
    sf::RenderWindow window_;
    std::unique_ptr<State> currentState_;
    MenuPlayData menuPlayData_;
};