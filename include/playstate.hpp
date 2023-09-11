#pragma once

#include "state.hpp"
#include "conductor.hpp"

class PlayState : public State {
public:
    PlayState();
    State::Type Update() override;
    void HandleEvents(sf::RenderWindow&, sf::Event&) override;
    void Render(sf::RenderWindow&) override;
    State::Type GetType() const override;

private:
    Conductor conductor_;
};