#pragma once

#include <SFML/Audio.hpp>
#include <thread>
#include "state.hpp"
#include "gamedata.hpp"
#include "configdata.hpp"
#include "MidiFile.h"


class LoadState : public State {
public:
    LoadState(GameData& gameData, const ConfigData& configData);
    State::Type Update(sf::Time dt) override;
    void HandleEvents(sf::RenderWindow& window, sf::Event& event) override;
    void Render(sf::RenderWindow& window) override;
private:
    void load();
    std::string findFileByExtension(const std::string& path, const std::string& ext) const;
    void readMidi();
    void readAudio();
    GameData& gameData_;
    const ConfigData& configData_;
    std::thread loadThread_;
    smf::MidiFile midiFile_;
    bool isLoaded_ = false;
};