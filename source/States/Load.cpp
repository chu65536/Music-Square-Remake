#include <iostream>
#include <cmath>
#include <filesystem>
#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Load.hpp"
#include "Tools/Parser.hpp"
#include "Tools/Debug.hpp"
#include "Tools/InterfaceTool.hpp"
#include "Tools/Filesystem.hpp"
#include "Game/Screen.hpp"
#include "Game/MapGenerator.hpp"
#include <fstream>
#include "Data/ParsedMapData.hpp"


Load::Load(GameData& gameData, const SettingsData& settingsData, const InterfaceData& interfaceData) :
    m_gameData(gameData),
    m_settingsData(settingsData),
    m_interfaceData(interfaceData),
    m_loadThread(std::thread(&Load::load, this))
{    
}

void Load::HandleEvents(sf::RenderWindow& window, sf::Event& event) 
{
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Keyboard::Key key = event.key.code;
        switch(key) 
        {
        }
    }
}

State::Type Load::Update(const sf::Time& dt) 
{
    State::Type returnValue = State::Type::None;
    m_timer += dt.asSeconds();
    updateText();
    loading();
    if(m_isLoaded) 
    {   
        returnValue = (m_gameData.newMap ? State::Type::MapSelection : State::Type::Play);
        m_gameData.newMap = false;
        m_loadThread.join();
    }
    return returnValue;
}

void Load::Render(sf::RenderWindow& window) 
{
}

void Load::load() 
{   
    if (m_gameData.newMap)
    {
        readMidi();
        m_gameData.songData.tracks.clear();
        Parser::ParseMidi(m_gameData.songData);   
        makeNewMapFile();
    }
    else
    {
        ParsedMapData data = Parser::ParseMap(m_gameData.chosenMapPath);
        // TODO: thread pool
        for (int track = 0; track < data.tracks.size(); ++track)
        {
            makeScreen(data.tracks[track], track);
        }
    }
    m_isLoaded = true;
}

void Load::makeScreen(const ParsedMapData::Track& data, int id)
{   
    sf::Vector2f startPoint = data.platforms.at(0).GetPosition();
    Square square(m_settingsData, startPoint);
    Map map(m_settingsData, data);
    Camera camera(startPoint, sf::Vector2f(m_settingsData.windowSize));
    Screen screen(id, std::move(square), std::move(map), std::move(camera));

    screen.SetViewport({0.f, 0.f, 0.f, 0.f});
    screen.CalcActiveTime(data.delays);
    screen.SetName(data.name);
    screen.SetFont(m_gameData.fontPath);
    m_gameData.screens.emplace_back(screen);
}

void Load::readMidi() 
{
    DEBUG_TIMER_START();
    std::string songPath = m_gameData.songsFolder + m_gameData.songData.chosenSongName;
    std::string filePath = fs::findAllByExt(songPath, ".mid").at(0);
    if (filePath != "") 
    {
        m_gameData.songData.midi.read(filePath);
    }
    DEBUG_TIMER_STOP("Midi loaded");
}

void Load::updateText() 
{
    int num = m_timer * 2;
    num %= 4;
    switch(num) 
    {
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

void Load::loading() 
{ 
    float x = m_interfaceData.workPos.x + m_interfaceData.workSize.x * 0.5f - 50.f;
    float y = m_interfaceData.workPos.y + m_interfaceData.workSize.y * 0.5f;

    ITools::DefaultWindowBegin({x, y}, {-FLT_MIN, -FLT_MIN}, 6, "Loading");
    ImGui::Text(m_loadingText.c_str());
    ITools::DefaultWindowEnd();
}

void Load::makeNewMapFile()
{   
    std::ofstream file;
    std::string path = "../resources/songs/" + m_gameData.songData.chosenSongName + "/" + m_gameData.newMapName + ".map";
    file.open(path);
    sf::Vector2f startPoint {0, 0};
    sf::Vector2f sqSz = m_settingsData.squareSize;

    file << "#square_size" << '\n';
    file << sqSz.x << ' ' << sqSz.y << ' ';
    file << '\n';
    for (int track = 0; track < m_gameData.songData.tracks.size(); track++)
    {   
        file << "#track " <<  m_gameData.songData.tracks[track].name << '\n';
        MapGenerator generator(m_settingsData);
        generator.Generate(m_gameData.songData.tracks[track], startPoint);
        generator.Export(file);
        startPoint.x += 100000.f;
    }
    file.close();
}