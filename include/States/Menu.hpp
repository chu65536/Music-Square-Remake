#pragma once

#include "States/State.hpp"
#include "Data/InterfaceData.hpp"


class Menu : public State 
{
public:
    Menu(const InterfaceData& interfaceData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
public:
    State::Type mainMenu();
    const InterfaceData& m_interfaceData;
};
