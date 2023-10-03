#pragma once

#include "States/State.hpp"
#include "Adds/Conductor.hpp"
#include "Data/GameData.hpp"
#include "Data/SettingsData.hpp"
#include "Game/Map.hpp"
#include "Game/Square.hpp"
#include "Adds/Camera.hpp"


class Play : public State {
public:
    Play(GameData& gameData, const SettingsData& settingsData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    GameData& m_gameData;
    Conductor m_conductor;
    Camera m_camera;
    float m_timer = 0.f;
    bool m_exit = false;
};