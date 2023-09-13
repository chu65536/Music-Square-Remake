#include <iostream>
#include <filesystem>
#include "imgui.h"
#include "imgui-SFML.h"
#include "loadstate.hpp"


LoadState::LoadState(GameData& data) :
    gameData_(data),
    isLoaded_(false) {
    loadThread_ = std::thread(&LoadState::load, this);
}

void LoadState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
}

State::Type LoadState::Update(sf::Time dt) {
    if(isLoaded_) {
        loadThread_.join();
        return State::Type::Play;
    }
    return State::Type::None;
}

void LoadState::Render(sf::RenderWindow& window) {
}

std::string LoadState::findFileByExtension(const std::string& path, const std::string& ext) const {
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ext) {
            return entry.path().string();
        }
    }

    std::cout << path << ": file with extension " << ext << " is not found" << std::endl;
    return "";
}

void LoadState::readMidi() {
    std::string songPath = "../resources/songs/" + gameData_.songName;
    std::string filePath = findFileByExtension(songPath, ".mid");
    if (filePath != "") {
        midiFile_.read(filePath);
    }
}

void LoadState::readAudio() {
    std::string songPath = "../resources/songs/" + gameData_.songName;
    std::string filePath = findFileByExtension(songPath, ".ogg");
    if (filePath != "") {
        gameData_.music.openFromFile(filePath);
    }
}

void LoadState::load() {
    readAudio();
    readMidi();
    for (size_t sec = 0; sec < 3; ++sec) {
        std::cout << "Generating Map..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000u));
    }
    isLoaded_ = true;
}
