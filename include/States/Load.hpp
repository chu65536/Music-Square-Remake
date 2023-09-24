#pragma once

#include <thread>
#include <mutex>
#include "States/State.hpp"
#include "Data/GameData.hpp"
#include "Data/UserData.hpp"


class Load : public State {
public:
    Load(GameData& gameData, const UserData& configData);
    State::Type Update(const sf::Time& dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void load();
    std::string findFileByExtension(const std::string& path, const std::string& ext) const;
    void readMidi();
    void readAudio();
    
    GameData& m_gameData;
    const UserData& m_configData;
    std::thread m_loadThread;
    std::mutex m_loadMutex;
    bool m_isLoaded = false;
};