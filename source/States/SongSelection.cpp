#include <iostream>
#include <filesystem>
#include "States/SongSelection.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


SongSelection::SongSelection(GameData& data) :
    m_gameData(data)
{
    loadSongs();
}

void SongSelection::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::Escape:
            m_exit = true;
            break;
        case sf::Keyboard::R:
            loadSongs();
            break;
        }
    }
}

State::Type SongSelection::Update(const sf::Time& dt) {
    if (m_exit) {
        return State::Type::Menu;
    }

    for (size_t i = 0; i < m_loadedSongs.size(); ++i) {   
        std::string song = m_loadedSongs[i];
        if (ImGui::Button(song.c_str(), ImVec2(-FLT_MIN, 0.0f))) {
            m_gameData.songData.chosenSongName = song;
            return State::Type::Load;
        }
    }
    return State::Type::None;
}

void SongSelection::Render(sf::RenderWindow& window) {
}


void SongSelection::loadSongs() {
    std::string path = "../resources/songs";
    if (!std::filesystem::is_directory(std::filesystem::path(path))) {
        std::cout << "Error: songs folder is not found" << std::endl;
        return;
    }
    
    m_loadedSongs.clear();
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        std::string song = entry.path().filename().string();
        m_loadedSongs.emplace_back(song);
    }
}