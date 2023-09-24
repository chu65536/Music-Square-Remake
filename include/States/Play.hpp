#pragma once

#include "States/State.hpp"
#include "Adds/Conductor.hpp"
#include "Data/GameData.hpp"
#include "Data/UserData.hpp"
#include "Game/map.hpp"
#include "Game/Square.hpp"
#include "Adds/Camera.hpp"


class Play : public State {
public:
    Play(GameData& gameData, UserData& userData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    GameData& m_gameData;
    UserData& m_userData;
    Conductor m_conductor;
    Camera m_camera;
    float m_timer = 0.f;
    bool m_exit = false;
};