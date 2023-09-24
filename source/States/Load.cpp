#include <iostream>
#include <filesystem>
#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Load.hpp"
#include "Adds/Parser.hpp"

Load::Load(GameData& gameData, const UserData& configData) :
    m_gameData(gameData),
    m_configData(configData), 
    m_loadThread(std::thread(&Load::load, this)) {
}

void Load::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        }
    }
}

State::Type Load::Update(const sf::Time& dt) {
    if(m_isLoaded) {
        m_loadThread.join();
        if (m_gameData.map.IsFailed()) {
            m_gameData.Clear();
            return State::Type::SongSelection;
        }
        else {
            return State::Type::Play;
        }
    }

    ImGui::Text("Loading...");
    
    return State::Type::None;
}

void Load::Render(sf::RenderWindow& window) {
}

void Load::load() {
    readAudio();
    readMidi();
    Parser parser;
    std::vector<double> delays = parser.Parse(m_gameData.midi);
    m_gameData.square.Init(m_configData);
    m_gameData.map.Init(delays, &m_configData, &m_gameData.square, m_loadMutex);
    m_isLoaded = true;
}

void Load::readMidi() {
    std::string songPath = "../resources/songs/" + m_gameData.songName;
    std::string filePath = findFileByExtension(songPath, ".mid");
    if (filePath != "") {
        m_gameData.midi.read(filePath);
    }
}

void Load::readAudio() {
    std::string songPath = "../resources/songs/" + m_gameData.songName;
    std::string filePath = findFileByExtension(songPath, ".ogg");
    if (filePath != "") {
        m_gameData.music.openFromFile(filePath);
    }
}

std::string Load::findFileByExtension(const std::string& path, const std::string& ext) const {
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ext) {
            return entry.path().string();
        }
    }

    std::cout << path << ": file with extension " << ext << " is not found" << std::endl;
    return "";
}
