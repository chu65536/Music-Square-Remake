#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "parser.hpp"
#include "gamedata.hpp"
#include "map.hpp"
#include "square.hpp"


class PlayState : public State {
public:
    PlayState(GameData& data);
    State::Type Update(sf::Time dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    GameData& gameData_;
    Conductor conductor_;
    Square& square_;
    Map& map_;
    float timer_ = 0.f;
    bool exit_ = false;
};