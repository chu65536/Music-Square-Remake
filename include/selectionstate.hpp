#pragma once

#include <vector>
#include "state.hpp"
#include "gamedata.hpp"


class SelectionState : public State {
public:
    SelectionState(GameData& data);
    State::Type Update(sf::Time dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    void loadSongs();
    GameData& gameData_;
    std::vector<std::string> loadedSongs;
    bool exit_ = false;
};