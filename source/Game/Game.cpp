#include <iostream>
#include "Game/Game.hpp"
#include "States/Menu.hpp"
#include "States/SongSelection.hpp"
#include "States/Settings.hpp"
#include "States/Load.hpp"
#include "States/Play.hpp"
#include "States/About.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tools/InterfaceTool.hpp"


Game::Game() {
    m_settingsData.Update();
    sf::ContextSettings windowSettings;
    windowSettings.antialiasingLevel = 8u;
    m_window.create(sf::VideoMode(m_settingsData.windowSize.x, m_settingsData.windowSize.y), "Music Square Remake", sf::Style::Fullscreen, windowSettings);
    m_window.setVerticalSyncEnabled(true);
    m_gameData.windowPt = &m_window;
    m_currentState = std::make_unique<Menu>(m_interfaceData);
    State::Type m_currentStateType = State::Type::Menu;
    m_gameData.Clear();
    m_backgroundScene.Init(m_settingsData);
}
    
void Game::Run() {
    initImGui();
    while (m_window.isOpen()) {
        handleEvents();
        update();
        render();
    }   
    ImGui::SFML::Shutdown();
}

void Game::handleEvents() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(m_window, event);
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key key = event.key.code;
            switch(key) {
            case sf::Keyboard::F:
                m_settingsData.fpsCounter = !m_settingsData.fpsCounter;
                break; 
            }
        }
        m_currentState->HandleEvents(m_window, event);
    }
}
 
void Game::update() {
    sf::Time deltaTime = m_clock.restart();
    ImGui::SFML::Update(m_window, deltaTime);
    m_interfaceData.Update();
    if (m_settingsData.fpsCounter) {
        fpsCounter(deltaTime);
    }
    if (m_currentStateType != State::Type::Play) {
        m_backgroundScene.Update(deltaTime);
    }
    State::Type nextStateType = m_currentState->Update(deltaTime);
    setState(nextStateType);
    if (nextStateType == State::Type::Play) {
        m_screenColor = m_settingsData.wallsColor;
    }
}

void Game::render() {
    m_window.clear(m_settingsData.wallsColor);
    if (m_currentStateType != State::Type::Play && m_currentStateType != State::Type::Load) {
        m_backgroundScene.Render(m_window);
    }
    m_currentState->Render(m_window);
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void Game::setState(State::Type type) {  
    if (type == State::Type::None) return;
    srand(time(0));
    switch (type) {
    case State::Type::Exit:
        m_window.close();
        break;
    case State::Type::Menu:
        m_currentState = std::make_unique<Menu>(m_interfaceData);
        m_currentStateType = State::Type::Menu;
        break;  
    case State::Type::SongSelection:
        m_currentState = std::make_unique<SongSelection>(m_gameData, m_interfaceData);
        m_currentStateType = State::Type::SongSelection;
        break;
    case State::Type::Settings:
        m_currentState = std::make_unique<Settings>(m_settingsData, m_interfaceData);
        m_currentStateType = State::Type::Settings;
        break;
    case State::Type::Load:
        m_currentState = std::make_unique<Load>(m_gameData, m_settingsData, m_interfaceData);
        m_currentStateType = State::Type::Load;
        break;
    case State::Type::Play:
        m_currentState = std::make_unique<Play>(m_gameData, m_settingsData);
        m_currentStateType = State::Type::Play;
        break;
    case State::Type::About:
        m_currentState = std::make_unique<About>();
        m_currentStateType = State::Type::About;
        break;
    }
}

void Game::initImGui() {
    if (!ImGui::SFML::Init(m_window)) {
        std::cerr << "ImGui-SFML init failed" << std::endl;
    }
    ImGuiIO &IO = ImGui::GetIO();
    IO.IniFilename = NULL;
    for (size_t i = 1; i <= 10; ++i)
    {
        IO.Fonts->AddFontFromFileTTF("../resources/fonts/square-deal.ttf", i * 10);
    }
    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "ImGui-SFML font load failed" << std::endl;
    }
}

void Game::fpsCounter(const sf::Time& dt) const 
{   
    std::string fps = std::to_string(1.f / dt.asSeconds());
    ITools::DefaultWindowBegin({0.f, 0.f}, {100.f, -FLT_MIN}, 3, "fps");
    ImGui::Text(fps.c_str());
    ITools::DefaultWindowEnd();
}

