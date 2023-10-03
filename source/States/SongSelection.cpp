#include <iostream>
#include <filesystem>
#include "States/SongSelection.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


SongSelection::SongSelection(GameData& data, const InterfaceData& interfaceData) :
    m_gameData(data),
    m_interfaceData(interfaceData)
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
    State::Type returnValue = State::Type::None;
    returnValue = selectionMenu();
    if (m_exit) {
        returnValue = State::Type::Menu;
    }
    return returnValue;
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

State::Type SongSelection::selectionMenu() {
    State::Type returnValue = State::Type::None;

    ImVec2 m_windowpos, m_windowpos_pivot;
    m_windowpos.x = m_interfaceData.workPos.x + 50.f;
    m_windowpos.y = m_interfaceData.workPos.y + m_interfaceData.workSize.y / 3;
    ImGui::SetNextWindowPos(m_windowpos, ImGuiCond_Always, m_windowpos_pivot);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::PushStyleColor(ImGuiCol_Button, m_interfaceData.frontColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_interfaceData.hoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_interfaceData.clickedColor);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[6]);
    ImGui::Begin("Selection menu", NULL, windowFlags);
    for (size_t i = 0; i < m_loadedSongs.size(); ++i) {   
        std::string song = m_loadedSongs[i];
        if (ImGui::Button(song.c_str(), ImVec2(m_interfaceData.selectionBtnSz.x, m_interfaceData.selectionBtnSz.y))) {
            m_gameData.songData.chosenSongName = song;
            returnValue =  State::Type::Load;
        }
    }
    ImGui::End();
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    return returnValue;
}