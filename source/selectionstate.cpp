#include <iostream>
#include <filesystem>
#include "selectionstate.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


SelectionState::SelectionState(GameData& data) :
    gameData_(data)
{
    loadSongs();
}

void SelectionState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::Escape:
            exit_ = true;
            break;
        case sf::Keyboard::R:
            loadSongs();
            break;
        }
    }
}

State::Type SelectionState::Update(sf::Time dt) {
    if (exit_) {
        return State::Type::Menu;
    }

    for (size_t i = 0; i < loadedSongs.size(); ++i) {   
        std::string song = loadedSongs[i];
        if (ImGui::Button(song.c_str(), ImVec2(-FLT_MIN, 0.0f))) {
            gameData_.songName = song;
            return State::Type::Load;
        }
    }
    return State::Type::None;
}

void SelectionState::Render(sf::RenderWindow& window) {
}


void SelectionState::loadSongs() {
    std::string path = "../resources/songs";
    if (!std::filesystem::is_directory(std::filesystem::path(path))) {
        std::cout << "Error: songs folder is not found" << std::endl;
        return;
    }
    
    loadedSongs.clear();
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::string song = entry.path().filename().string();
        loadedSongs.emplace_back(song);
    }
}