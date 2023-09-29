#include <iostream>
#include "Game/Game.hpp"
#include "States/Menu.hpp"
#include "States/SongSelection.hpp"
#include "States/Settings.hpp"
#include "States/Load.hpp"
#include "States/Play.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


Game::Game() {
    m_window.create(sf::VideoMode(m_gameData.windowSize.x, m_gameData.windowSize.y), "Music Square Remake", sf::Style::Fullscreen);
    m_gameData.windowPt = &m_window;
    m_currentState = std::make_unique<Menu>();
    m_gameData.Update();
}

void Game::Run() {
    bool imgui = ImGui::SFML::Init(m_window);
    ImGui::GetIO().IniFilename = NULL;
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
            case sf::Keyboard::D:
                m_gameData.debugWindow = !m_gameData.debugWindow;
                break; 
            }
        }
        m_currentState->HandleEvents(m_window, event);
    }
}
 
void Game::update() {
    sf::Time deltaTime = m_clock.restart();
    ImGui::SFML::Update(m_window, deltaTime);
    if (m_gameData.debugWindow) {
        debugWindow(deltaTime);
    }
    State::Type nextStateType = m_currentState->Update(deltaTime);
    setState(nextStateType);
}

void Game::render() {
    m_window.clear(m_gameData.wallsColor); 
    m_currentState->Render(m_window);
    ImGui::SFML::Render(m_window);
    m_window.display();
}

void Game::setState(State::Type type) {  
    if (type == State::Type::None) return;
    srand(time(0));
    switch (type) {
    case State::Type::Menu:
        m_currentState = std::make_unique<Menu>();
        break;  
    case State::Type::SongSelection:
        m_currentState = std::make_unique<SongSelection>(m_gameData);
        break;
    case State::Type::Settings:
        m_currentState = std::make_unique<Settings>(m_gameData);
        break;
    case State::Type::Load:
        m_currentState = std::make_unique<Load>(m_gameData);
        break;
    case State::Type::Play:
        m_currentState = std::make_unique<Play>(m_gameData);
        break;
    }
}

void Game::debugWindow(const sf::Time& dt) const {
    int location = 0;
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing;
    const float PAD = 0.0f;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 work_size = viewport->WorkSize;
    ImVec2 m_windowpos, m_windowpos_pivot;
    m_windowpos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
    m_windowpos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
    m_windowpos_pivot.x = (location & 1) ? 1.0f : 0.0f;
    m_windowpos_pivot.y = (location & 2) ? 1.0f : 0.0f;
    ImGui::SetNextWindowPos(m_windowpos, ImGuiCond_Always, m_windowpos_pivot);

float dtSec = dt.asSeconds();
    float fps = 1.f / dtSec;
    std::string fpsStr = "FPS: " + std::to_string(fps);

    sf::Vector2f squarePos = m_gameData.square.GetPositionRef();
    std::string sqaurePosStr = "Square position\nX: " + std::to_string(squarePos.x) + " Y: " + std::to_string(squarePos.y);
    if (ImGui::Begin("Debug info", NULL, windowFlags))
    {
        ImGui::Text(fpsStr.c_str(), NULL);
        ImGui::Text(sqaurePosStr.c_str(), NULL);
    }
    ImGui::End();
}

