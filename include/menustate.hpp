#pragma once

#include "state.hpp"

class MenuState : public State {
public:
    MenuState();
    State::Type update() override;
    void render(sf::RenderWindow&) override;
    State::Type getType() const override;
};