#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "conductor.hpp"

class Game {
public:
    Game();
    void Run();

private:
    sf::RenderWindow window_;
    Conductor conductor_;
    State* currentState_;
};