#include "imgui.h"
#include "imgui-SFML.h"
#include "menustate.hpp"

#include <iostream>
#include <filesystem>


MenuState::MenuState(MenuPlayData& data) :
    menuPlayData_(data) {
    loadSongs();
}

State::Type MenuState::GetType() const { return State::Type::Menu; }

void MenuState::loadSongs() {
    std::string path = "../resources/songs";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::string song = entry.path().filename();
        loadedSongs.emplace_back(song);
        std::cout << song << " - Loaded!" <<  std::endl;
    }
}

void MenuState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::R:
            loadSongs();
            break;
        }
    }
}

State::Type MenuState::Update() {
    for (size_t i = 0; i < loadedSongs.size(); ++i) {   
        std::string song = loadedSongs[i];
        if (ImGui::Button(song.c_str(), ImVec2(-FLT_MIN, 0.0f))) {
            std::cout << "playing song - " << song << std::endl;
            menuPlayData_.chosenSong = song;
            return State::Type::Play;
        }
    }

    return State::Type::Menu;
}

void MenuState::Render(sf::RenderWindow& window) {
    window.clear(); 
    ImGui::SFML::Render(window);
    window.display();
}
