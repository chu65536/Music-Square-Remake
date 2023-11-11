#include <iostream>
#include <filesystem>
#include "States/SongSelection.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tools/InterfaceTool.hpp"


SongSelection::SongSelection(GameData& data, const InterfaceData& interfaceData) :
    m_gameData(data),
    m_interfaceData(interfaceData)
{
    loadSongs();
}

void SongSelection::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) 
    {
        sf::Keyboard::Key key = event.key.code;
        switch(key) 
        {
        case sf::Keyboard::Escape:
            m_exit = true;
            break;
        case sf::Keyboard::R:
            loadSongs();
            break;
        }
    }
}

State::Type SongSelection::Update(const sf::Time& dt) 
{
    State::Type returnValue = State::Type::None;
    returnValue = selectionMenu();
    if (m_exit) 
    {
        returnValue = State::Type::Menu;
    }
    return returnValue;
}

void SongSelection::Render(sf::RenderWindow& window) 
{
}

void SongSelection::loadSongs() 
{
    const std::string path = "../../resources/songs";
    if (!std::filesystem::is_directory(std::filesystem::path(path))) 
    {
        std::cerr << "Error: songs folder is not found" << std::endl;
        return;
    }
    
    m_loadedSongs.clear();
    for (const auto& entry: std::filesystem::directory_iterator(path)) 
    {
        std::string song = entry.path().filename().string();
        m_loadedSongs.emplace_back(song);
    }
}

State::Type SongSelection::selectionMenu() 
{
    State::Type returnValue = State::Type::None;

    float w = m_interfaceData.workSize.x / 3.f;
    float h = m_interfaceData.workSize.y / 8.f * 5.5f;
    float x = m_interfaceData.workPos.x;
    float y = m_interfaceData.workSize.y / 8.f;
    float btnY = h / 12.f;

    ITools::DefaultWindowBegin({x, y}, {w, h}, 4, "Selection");
    for (size_t i = 0; i < m_loadedSongs.size(); ++i) 
    {   
        const std::string song = m_loadedSongs[i];
        if (ImGui::Button(song.c_str(), {-FLT_MIN, btnY})) 
        {
            m_gameData.songData.chosenSongName = song;
            returnValue =  State::Type::Load;
        }
    }
    ITools::DefaultWindowEnd();

    ITools::DefaultWindowBegin({x, y + h}, {w, m_interfaceData.workSize.y / 8.f * 0.5f}, 5, "Back");
    if (ImGui::Button("Back", {-FLT_MIN, -FLT_MIN}))
    {
        returnValue = State::Type::Menu;
    }
    ITools::DefaultWindowEnd();

    return returnValue;
}