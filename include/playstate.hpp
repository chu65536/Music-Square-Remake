#pragma once

#include "state.hpp"

class PlayState : public State {
public:
    PlayState();
    State::Type update() override;
    void render(sf::RenderWindow&) override;
    State::Type getType() const override;
};