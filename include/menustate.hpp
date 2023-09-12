#pragma once

#include <vector>
#include "state.hpp"
#include "gamedata.hpp"


class MenuState : public State {
public:
    MenuState(GameData& data);
    State::Type Update(sf::Time dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    GameData& gameData_;
    std::vector<std::string> loadedSongs;
    void loadSongs();
};