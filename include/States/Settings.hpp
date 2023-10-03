#pragma once

#include "States/State.hpp"
#include "Data/SettingsData.hpp"

class Settings : public State {
public:
    Settings(SettingsData& settingsData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void configMenu();
    SettingsData& m_settingsData;
    bool m_exit = false;
};