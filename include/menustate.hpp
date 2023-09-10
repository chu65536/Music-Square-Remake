#pragma once

#include "state.hpp"

class MenuState : public State {
public:
    MenuState();
    State* handleEvent(const sf::Event&) override;
    void update(sf::Time) override;
    void render(sf::RenderWindow&) override;
};