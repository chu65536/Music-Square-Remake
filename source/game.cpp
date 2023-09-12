#include <iostream>
#include "game.hpp"
#include "menustate.hpp"
#include "playstate.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

Game::Game() {
    window_.create(sf::VideoMode(800u, 800u), "Title");
    window_.setKeyRepeatEnabled(false);
    ImGui::SFML::Init(window_);
    ImGui::GetIO().IniFilename = NULL;
    menuPlayData_ = MenuPlayData();
    currentState_ = std::make_unique<MenuState>(menuPlayData_);
}

// Global events, working across all states
void Game::handleGlobalEvents() {
    sf::Event event;
    while(window_.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            sf::Keyboard::Key key = event.key.code;
            switch(key) {
            case sf::Keyboard::Escape:
                window_.close();
                break;
            }
        }
        // Local events specific for every state
        currentState_->HandleEvents(window_, event);
    }
}

// Each transition instantiate new state sample 
void Game::updateState(State::Type type) {
    if (type == currentState_->GetType()) return;
    
    switch (type) {
    case State::Type::Menu:
        currentState_ = std::make_unique<MenuState>(menuPlayData_);
        break;  
    case State::Type::Play:
        currentState_ = std::make_unique<PlayState>(menuPlayData_);
        break;
    }
}

void Game::Run() {
    sf::Clock clock;
    while (window_.isOpen()) {
        sf::Time dt = clock.restart();
        handleGlobalEvents();
        ImGui::SFML::Update(window_, dt);
        State::Type nextStateType = currentState_->Update();
        updateState(nextStateType);
        ImGui::SFML::Render(window_);
        currentState_->Render(window_);
    }   
    ImGui::SFML::Shutdown();
}



