#include <iostream>
#include <filesystem>
#include "States/MapSelection.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tools/InterfaceTool.hpp"
#include "Tools/Filesystem.hpp"
#include "misc/cpp/imgui_stdlib.h"


MapSelection::MapSelection(GameData& gameData, const InterfaceData& interfaceData) :
    m_gameData(gameData),
    m_interfaceData(interfaceData)
{
    loadMaps();
    m_gameData.newMapName = "new map " + std::to_string(m_loadedMaps.size() + 1);
}

void MapSelection::HandleEvents(sf::RenderWindow& window, sf::Event& event) 
{
    if (event.type == sf::Event::KeyPressed) 
    {
        sf::Keyboard::Key key = event.key.code;
        switch(key) 
        {
        case sf::Keyboard::Escape:
            m_exit = true;
            break;
        case sf::Keyboard::R:
            loadMaps();
            break;
        }
    }
}

State::Type MapSelection::Update(const sf::Time& dt) 
{
    State::Type returnValue = State::Type::None;
    returnValue = selectionMenu();
    if (m_exit) 
    {
        returnValue = State::Type::MapSelection;
    }
    return returnValue;
}

void MapSelection::Render(sf::RenderWindow& window) 
{
}

void MapSelection::loadMaps() 
{   
    std::string song = m_gameData.songData.chosenSongName;
    const std::string path = "../resources/songs/" + song;
    if (!std::filesystem::is_directory(std::filesystem::path(path))) 
    {
        std::cerr << "Error: " + song + " folder is not found" << std::endl;
        return;
    }
    
    m_loadedMaps.clear();
    m_loadedMaps = fs::findAllByExt(path, ".map");
}

State::Type MapSelection::selectionMenu() 
{
    State::Type returnValue = State::Type::None;

    float w = m_interfaceData.workSize.x / 3.f;
    float h = m_interfaceData.workSize.y / 8.f * 5.0f;
    float x = m_interfaceData.workPos.x;
    float y = m_interfaceData.workSize.y / 8.f;
    float btnY = h / 12.f;
    float menuBtnY = m_interfaceData.workSize.y / 8.f * 0.5f;

    ITools::DefaultWindowBegin({x, y}, {w, menuBtnY}, 4, "New map");
    if (ImGui::Button("Generate", {w * 0.5f, -FLT_MIN}))
    {
        m_gameData.newMap = true;
        returnValue = State::Type::Load;
    } ImGui::SameLine();
    ImGui::InputText("New map name", &m_gameData.newMapName);
    ITools::DefaultWindowEnd();

    ITools::DefaultWindowBegin({x, y + menuBtnY}, {w, h}, 3, "Map Selection");
    for (size_t i = 0; i < m_loadedMaps.size(); ++i) 
    {   
        const std::string mapPath = m_loadedMaps[i];
        const std::string mapName = std::filesystem::path(mapPath).stem();
        if (ImGui::Button(mapName.c_str(), {-FLT_MIN, btnY})) 
        {
            m_gameData.chosenMapPath = mapPath;
            returnValue =  State::Type::Load;
        }
    }
    ITools::DefaultWindowEnd();

    ITools::DefaultWindowBegin({x, y + h + menuBtnY}, {w, menuBtnY}, 4, "Back");
    if (ImGui::Button("Back", {-FLT_MIN, -FLT_MIN}))
    {
        returnValue = State::Type::SongSelection;
    }
    ITools::DefaultWindowEnd();

    return returnValue;
}