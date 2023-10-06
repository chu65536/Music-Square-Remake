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

    ImVec2 windowPosition, windowSize;
    windowSize.x = m_interfaceData.workSize.x / 3.f;
    windowSize.y = m_interfaceData.workSize.y / 3.f;
    windowPosition.x = windowSize.x;
    windowPosition.y = windowSize.y;
    ImGui::SetNextWindowPos(windowPosition, ImGuiCond_Always, m_interfaceData.workPosPivot);
    ImGui::SetNextWindowSize(windowSize);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_Button, m_interfaceData.frontColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_interfaceData.hoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_interfaceData.clickedColor);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[4]);
    if (ImGui::Begin("Main Menu", NULL, windowFlags)) {
        for (size_t i = 0; i < m_loadedSongs.size(); ++i) {   
            std::string song = m_loadedSongs[i];
            if (ImGui::Button(song.c_str(), ImVec2(-FLT_MIN, windowSize.y / 8.f))) {
                m_gameData.songData.chosenSongName = song;
                returnValue =  State::Type::Load;
            }
        }
    }
    ImGui::End();

    ImVec2 buttonSize(windowSize.x, m_interfaceData.workSize.y / 10.f);
    ImVec2 buttonPosition(windowPosition.x, windowSize.y * 2.f);
    ImGui::SetNextWindowPos(buttonPosition);
    ImGui::SetNextWindowSize(buttonSize);
    ImGui::PushStyleColor(ImGuiCol_Button, m_interfaceData.frontColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_interfaceData.hoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_interfaceData.clickedColor);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[6]);
    if (ImGui::Begin("Back button", NULL, windowFlags)) {
        if (ImGui::Button("Back", ImVec2(-FLT_MIN, -FLT_MIN))) {
            returnValue = State::Type::Menu;
        }
    }
    ImGui::PopFont();
    ImGui::End();
    ImGui::PopFont();
    ImGui::PopStyleColor(6);
    ImGui::PopStyleVar(3);
    return returnValue;
}