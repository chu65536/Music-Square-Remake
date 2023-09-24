#pragma once

#include "States/State.hpp"
#include "Data/UserData.hpp"

class Settings : public State {
public:
    Settings(UserData& data);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void configMenu();
    UserData& m_userData;
    bool m_exit = false;
};