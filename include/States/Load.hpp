#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include "States/State.hpp"
#include "Data/GameData.hpp"
#include "Data/SettingsData.hpp"
#include "Data/InterfaceData.hpp"


class Load : public State 
{
public:
    Load(GameData& gameData, const SettingsData& settingsData, const InterfaceData& interfaceData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void load();
    void readMidi();
    void readAudio();
    void loading();
    void updateText();
    void makeScreen(const ParsedMapData::Track& data, int id);
    void makeNewMapFile();
    
    GameData& m_gameData;
    const SettingsData& m_settingsData;
    const InterfaceData& m_interfaceData;
    std::thread m_loadThread;
    float m_timer = 0.f;
    bool m_isLoaded = false;
    std::string m_loadingText;
};