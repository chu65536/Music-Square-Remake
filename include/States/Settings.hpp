#pragma once

#include "States/State.hpp"
#include "Data/GameData.hpp"

class Settings : public State {
public:
    Settings(GameData& data);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void configMenu();
    GameData& m_gameData;
    bool m_exit = false;
};