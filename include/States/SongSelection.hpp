#pragma once

#include "States/State.hpp"
#include "Data/GameData.hpp"


class SongSelection : public State {
public:
    SongSelection(GameData& data);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    void loadSongs();
    GameData& m_gameData;
    std::vector<std::string> m_loadedSongs;
    bool m_exit = false;
};