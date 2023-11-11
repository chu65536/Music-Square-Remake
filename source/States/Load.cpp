#include <iostream>
#include <cmath>
#include <filesystem>
#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Load.hpp"
#include "Tools/Parser.hpp"
#include "Tools/Debug.hpp"
#include "Tools/InterfaceTool.hpp"

const std::string songsFolder = "../../resources/songs/";

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
        returnValue = State::Type::Play;
        m_loadThread.join();
    }
    return returnValue;
}

void Load::Render(sf::RenderWindow& window) 
{
}

void Load::load() 
{
    readAudio();
    readMidi();
    Parser::Parse(m_gameData.songData);

    int tracksNum = m_gameData.songData.tracks.size();
    std::deque<sf::FloatRect> q;
    makeViewports(tracksNum, q);
    std::vector<sf::FloatRect> viewports = {q.begin(), q.end()};

    sf::Vector2f startPoint(0.f, 0.f);
    // Thread pool opportunity!!!
    for (size_t i = 0; i < tracksNum; ++i)
    {   
        DEBUG_TIMER_START();
        m_gameData.screens.emplace_back(GameData::Screen());
        m_gameData.screens[i].square.Init(m_settingsData, startPoint);
        m_gameData.screens[i].map.Init(&m_settingsData, &m_gameData.songData.tracks[i], startPoint);
        m_gameData.screens[i].camera.Init(m_gameData.windowPt, viewports[i], m_gameData.screens[i].square.GetPositionRef(), startPoint, sf::Vector2f(m_settingsData.windowSize));

        DEBUG_TIMER_STOP("Map for track " + std::to_string(i) + " generated");
        startPoint.x += 100'000.f;
    }
    m_isLoaded = true;
}

void Load::readMidi() 
{
    DEBUG_TIMER_START();
    std::string songPath = songsFolder + m_gameData.songData.chosenSongName;
    std::string filePath = findFileByExtension(songPath, ".mid");
    if (filePath != "") 
    {
        m_gameData.songData.midi.read(filePath);
    }
    DEBUG_TIMER_STOP("Midi loaded");
}

void Load::readAudio() 
{
    DEBUG_TIMER_START();
    std::string songPath = songsFolder + m_gameData.songData.chosenSongName;
    std::string filePath = findFileByExtension(songPath, ".ogg");
    if (filePath != "") 
    {
        m_gameData.songData.music.openFromFile(filePath);
    }
    DEBUG_TIMER_STOP("Audio loaded");
}

void Load::makeViewports(unsigned int n, std::deque<sf::FloatRect>& q)
{   
    if (q.empty())
    {
        q.emplace_back(0.f, 0.f, 1.f, 1.f);
        n--;
    }
    if (n == 0) return;

    sf::FloatRect cur = q.front();
    q.pop_front();

    sf::FloatRect h1, h2;
    h1 = h2 = cur;
    if (cur.width >= cur.height)
    {   
        h1.width /= 2.f;

        h2.left = cur.left + cur.width / 2.f;
        h2.width /= 2.f;
    }
    else
    {
        h1.height /= 2.f;

        h2.top = cur.top + cur.height / 2.f;
        h2.height /= 2.f;        
    }

    q.push_back(h1);
    q.push_back(h2);

    makeViewports(n - 1, q);
}

GameData::Screen Load::makeScreen(const sf::FloatRect& viewport, const SongData::Track& track, const sf::Vector2f& startPoint)
{
    GameData::Screen screen;
    return screen;
}

std::string Load::findFileByExtension(const std::string& path, const std::string& ext) const 
{
    for (const auto & entry: std::filesystem::directory_iterator(path)) 
    {
        if (entry.path().extension() == ext) 
        {
            return entry.path().string();
        }
    }

    std::cout << path << ": file with extension " << ext << " is not found" << std::endl;
    return "";
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
