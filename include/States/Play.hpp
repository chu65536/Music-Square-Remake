#pragma once

#include "States/State.hpp"
#include "Game/Conductor.hpp"
#include "Data/GameData.hpp"
#include "Data/SettingsData.hpp"
#include "Game/Map.hpp"
#include "Game/Square.hpp"
#include "Game/Camera.hpp"
#include "Game/Screen.hpp"
#include <deque>

class Play : public State 
{
public:
    Play(GameData& gameData, const SettingsData& settingsData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void updateViewports();
    void addViewport(std::deque<sf::FloatRect>& dq);
    void removeScreen(int id);

    GameData& m_gameData;
    const SettingsData& m_settingsData;
    Conductor m_conductor;
    float m_timer = 0.f;
    bool m_exit = false;
    std::vector<Screen*> m_activeScreens;
};