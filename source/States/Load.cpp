#include <iostream>
#include <cmath>
#include <filesystem>
#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Load.hpp"
#include "Adds/Parser.hpp"
#include "Adds/Debug.hpp"


Load::Load(GameData& gameData, const SettingsData& settingsData, const InterfaceData& interfaceData) :
    m_gameData(gameData),
    m_settingsData(settingsData),
    m_interfaceData(interfaceData),
    m_loadThread(std::thread(&Load::load, this)) {}

void Load::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        }
    }
}

State::Type Load::Update(const sf::Time& dt) {
    State::Type returnValue = State::Type::None;
    m_timer += dt.asSeconds();
    updateText();
    loading();
    if(m_isLoaded) {
        m_loadThread.join();
        if (m_gameData.map.IsFailed()) {
            m_gameData.Clear();
            returnValue = State::Type::SongSelection;
        }
        else {
            returnValue = State::Type::Play;
        }
    }
    return returnValue;
}

void Load::Render(sf::RenderWindow& window) {
}

void Load::load() {
    readAudio();
    readMidi();
    Parser::Parse(m_gameData.songData);
    m_gameData.square.Init(m_settingsData);
    m_gameData.map.Init(&m_settingsData, &m_gameData.songData);
    m_isLoaded = true;
}

void Load::readMidi() {
    DEBUG_TIMER_START();
    std::string songPath = "../resources/songs/" + m_gameData.songData.chosenSongName;
    std::string filePath = findFileByExtension(songPath, ".mid");
    if (filePath != "") {
        m_gameData.songData.midi.read(filePath);
    }
    DEBUG_TIMER_STOP("Midi loaded");
}

void Load::readAudio() {
    DEBUG_TIMER_START();
    std::string songPath = "../resources/songs/" + m_gameData.songData.chosenSongName;
    std::string filePath = findFileByExtension(songPath, ".ogg");
    if (filePath != "") {
        m_gameData.songData.music.openFromFile(filePath);
    }
    DEBUG_TIMER_STOP("Audio loaded");
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

void Load::updateText() {
    int num = m_timer * 2;
    num %= 4;
    switch(num) {
    case 0:
        m_loadingText = "Loading";
        break;
    case 1:
        m_loadingText = "Loading.";
        break;
    case 2:
        m_loadingText = "Loading..";
        break;
    case 3:
        m_loadingText = "Loading...";
        break;
    }
}

void Load::loading() { 
    ImVec2 m_windowpos, m_windowpos_pivot;
    m_windowpos.x = m_interfaceData.workPos.x + m_interfaceData.workSize.x / 2 - 100.f;
    m_windowpos.y = m_interfaceData.workPos.y + m_interfaceData.workSize.y / 2;
    ImGui::SetNextWindowPos(m_windowpos, ImGuiCond_Always, m_windowpos_pivot);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[6]);
    ImGui::Begin("Main Menu", NULL, windowFlags);
    ImGui::Text(m_loadingText.c_str());
    ImGui::End();
    ImGui::PopFont();
}
