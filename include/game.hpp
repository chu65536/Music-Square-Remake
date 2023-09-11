#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "conductor.hpp"

class Game {
public:
    Game();
    void Run();
    void HandleEvents(sf::Event&);
    void UpdateState(State::Type);
private:
    sf::RenderWindow window_;
    State* currentState_;
};