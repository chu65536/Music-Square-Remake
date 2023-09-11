#pragma once

#include "state.hpp"


class MenuState : public State {
public:
    MenuState();
    State::Type Update() override;
    void HandleEvents(sf::RenderWindow&, sf::Event&) override;
    void Render(sf::RenderWindow&) override;
    State::Type GetType() const override;
};