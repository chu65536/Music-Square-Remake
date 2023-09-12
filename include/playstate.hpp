#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "menuplaydata.hpp"

class PlayState : public State {
public:
    PlayState(MenuPlayData&);
    State::Type Update() override;
    void HandleEvents(sf::RenderWindow&, sf::Event&) override;
    void Render(sf::RenderWindow&) override;
    State::Type GetType() const override;

private:
    MenuPlayData& menuPlaydata_;
    Conductor conductor_;
};