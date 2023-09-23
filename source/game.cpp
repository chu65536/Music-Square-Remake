#include <iostream>
#include "game.hpp"
#include "menustate.hpp"
#include "selectionstate.hpp"
#include "configstate.hpp"
#include "loadstate.hpp"
#include "playstate.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


Game::Game() {
    window_.create(sf::VideoMode(configData_.windowSize.x, configData_.windowSize.y), "Title", sf::Style::Fullscreen);
    gameData_.windowPt = &window_;
    bool imgui = ImGui::SFML::Init(window_);
    ImGui::GetIO().IniFilename = NULL;
    currentState_ = std::make_unique<MenuState>();
}

void Game::handleGlobalEvents() {
    sf::Event event;
    while(window_.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window_, event);
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key key = event.key.code;
            switch(key) {
            case sf::Keyboard::D:
                configData_.debugWindow = !configData_.debugWindow;
                break; 
            }
        }
        currentState_->HandleEvents(window_, event);
    }
}

void Game::setState(State::Type type) {  
    switch (type) {
    case State::Type::Menu:
        currentState_ = std::make_unique<MenuState>();
        break;  
    case State::Type::Selection:
        currentState_ = std::make_unique<SelectionState>(gameData_);
        break;
    case State::Type::Config:
        currentState_ = std::make_unique<ConfigState>(configData_);
        break;
    case State::Type::Load:
        currentState_ = std::make_unique<LoadState>(gameData_, configData_);
        break;
    case State::Type::Play:
        currentState_ = std::make_unique<PlayState>(gameData_, configData_);
        break;
    }
}

void Game::Run() {
    sf::Clock clock;
    srand(time(0));
    while (window_.isOpen()) {
        sf::Time dt = clock.restart();
        handleGlobalEvents();

        ImGui::SFML::Update(window_, dt);
        State::Type nextStateType = currentState_->Update(dt);
        setState(nextStateType);

        window_.clear(sf::Color(200, 200, 200)); 
        currentState_->Render(window_);
        if (configData_.debugWindow) {
            debugWindow(gameData_, configData_, dt);
        }
        ImGui::SFML::Render(window_);
        window_.display();
    }   
    ImGui::SFML::Shutdown();
}

void Game::debugWindow(const GameData& gameData, const ConfigData& configData, const sf::Time& dt) const {
    int location = 0;
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing;
    const float PAD = 0.0f;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 work_size = viewport->WorkSize;
    ImVec2 window_pos, window_pos_pivot;
    window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
    window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
    window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
    window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

    float dtSec = dt.asSeconds();
    float fps = 1.f / dtSec;
    std::string fpsStr = "FPS: " + std::to_string(fps);

    sf::Vector2f squarePos = gameData_.square.GetPosition();
    std::string sqaurePosStr = "Square position\nX: " + std::to_string(squarePos.x) + " Y: " + std::to_string(squarePos.y);
    if (ImGui::Begin("Debug info", NULL, windowFlags))
    {
        ImGui::Text(fpsStr.c_str(), NULL);
        ImGui::Text(sqaurePosStr.c_str(), NULL);
    }
    ImGui::End();
}

