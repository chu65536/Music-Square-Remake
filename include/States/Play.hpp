#pragma once

#include "States/State.hpp"
#include "Game/Conductor.hpp"
#include "Data/GameData.hpp"
#include "Data/SettingsData.hpp"
#include "Game/Map.hpp"
#include "Game/Square.hpp"
#include "Game/Camera.hpp"


class Play : public State {
public:
    Play(GameData& gameData, const SettingsData& settingsData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    void drawBackground(sf::RenderWindow& window);

    GameData& m_gameData;
    Conductor m_conductor;
    float m_timer = 0.f;
    bool m_exit = false;
};