#pragma once

#include "state.hpp"
#include "conductor.hpp"
#include "parser.hpp"
#include "gamedata.hpp"
#include "map.hpp"
#include "square.hpp"
#include "camera.hpp"


class PlayState : public State {
public:
    PlayState(GameData& gameData, ConfigData& configData);
    State::Type Update(sf::Time dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    void settingsWindow();
    GameData& gameData_;
    ConfigData& configData_;
    Conductor conductor_;
    float timer_ = 0.f;
    bool exit_ = false;
};