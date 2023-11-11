#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include "States/State.hpp"
#include "Data/GameData.hpp"
#include "Data/SettingsData.hpp"
#include "Data/InterfaceData.hpp"


class Load : public State {
public:
    Load(GameData& gameData, const SettingsData& settingsData, const InterfaceData& interfaceData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void load();
    std::string findFileByExtension(const std::string& path, const std::string& ext) const;
    void readMidi();
    void readAudio();
    void loading();
    void updateText();
    GameData::Screen makeScreen(const sf::FloatRect& viewport, const SongData::Track& track, const sf::Vector2f& startPoint);
    void makeViewports(unsigned int n, std::deque<sf::FloatRect>& q);
    
    GameData& m_gameData;
    const SettingsData& m_settingsData;
    const InterfaceData& m_interfaceData;
    std::thread m_loadThread;
    std::mutex m_loadMutex;
    float m_timer = 0.f;
    bool m_isLoaded = false;
    std::string m_loadingText;
};