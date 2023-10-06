#pragma once

#include "States/State.hpp"
#include "Data/SettingsData.hpp"
#include "Data/InterfaceData.hpp"


class Settings : public State {
public:
    Settings(SettingsData& settingsData, const InterfaceData& interfaceData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    State::Type settingsMenu();
    SettingsData& m_settingsData;
    const InterfaceData& m_interfaceData;
    bool m_exit = false;
};