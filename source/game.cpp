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
    window_.create(sf::VideoMode(800u, 800u), "Title");
    ImGui::SFML::Init(window_);
    ImGui::GetIO().IniFilename = NULL;
    currentState_ = std::make_unique<MenuState>();
}

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
        currentState_ = std::make_unique<PlayState>(gameData_);
        break;
    }
}

void Game::Run() {
    sf::Clock clock;
    while (window_.isOpen()) {
        sf::Time dt = clock.restart();
        handleGlobalEvents();

        ImGui::SFML::Update(window_, dt);
        State::Type nextStateType = currentState_->Update(dt);
        setState(nextStateType);

        window_.clear(); 
        currentState_->Render(window_);
        ImGui::SFML::Render(window_);
        window_.display();
    }   
    ImGui::SFML::Shutdown();
}



