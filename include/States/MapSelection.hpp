#pragma once

#include "States/State.hpp"
#include "Data/GameData.hpp"
#include "Data/InterfaceData.hpp"


class MapSelection : public State 
{
public:
    MapSelection(GameData& data, const InterfaceData& interfaceData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;

private:
    void loadMaps();
    State::Type selectionMenu();

    GameData& m_gameData;
    const InterfaceData& m_interfaceData;
    std::vector<std::string> m_loadedMaps;
    bool m_exit = false;
};