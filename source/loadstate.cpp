#include <iostream>
#include <filesystem>
#include <mutex>
#include "imgui.h"
#include "imgui-SFML.h"
#include "loadstate.hpp"
#include "parser.hpp"


std::mutex m;

LoadState::LoadState(GameData& gameData, const ConfigData& configData) :
    gameData_(gameData),
    configData_(configData), 
    camera_(gameData_.windowPt, gameData_.map, configData_.position, sf::Vector2f(10000.f, 10000.f)),
    loadThread_(std::thread(&LoadState::load, this)) {
    camera_.speed = 1.f;
}

void LoadState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        }
    }
}

State::Type LoadState::Update(sf::Time dt) {
    if(isLoaded_) {
        loadThread_.join();
        if (gameData_.map.IsFailed()) {
            gameData_.Clear();
            return State::Type::Selection;
        }
        else {
            return State::Type::Play;
        }
    }
    
    camera_.Update(dt);
    return State::Type::None;
}

void LoadState::Render(sf::RenderWindow& window) {
    std::lock_guard<std::mutex> lock(m);
    gameData_.map.Render(window);
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
    Parser parser;
    std::vector<double> delays = parser.Parse(midiFile_);
    gameData_.square.Init(configData_);
    gameData_.map.Init(delays, &configData_, &gameData_.square, m);
    isLoaded_ = true;
}
