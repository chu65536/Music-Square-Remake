#include <iostream>
#include "game.hpp"
#include "menustate.hpp"
#include "playstate.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

Game::Game() {
    window_.create(sf::VideoMode(500u, 500u), "Title");
    window_.setKeyRepeatEnabled(false);
    ImGui::SFML::Init(window_);
    currentState_ = new MenuState;
}

void Game::HandleEvents(sf::Event& event) {
    while(window_.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(window_, event);
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
    }
}

void Game::UpdateState(State::Type type) {
    if (type == currentState_->getType()) return;
    
    std::cout << "deleted, allocating new state" << std::endl;
    delete currentState_;
    switch (type)
    {
    case State::Type::Menu:
        currentState_ = new MenuState;
        break;
    case State::Type::Play:
        currentState_ = new PlayState;
        break;
    }
}

void Game::Run() {
    sf::Clock clock;
    while (window_.isOpen()) {
        sf::Time dt = clock.restart();
        sf::Event event;
        HandleEvents(event);
        ImGui::SFML::Update(window_, dt);
        State::Type nextStateType = currentState_->update();
        UpdateState(nextStateType);
        ImGui::SFML::Render(window_);
        currentState_->render(window_);
    }   
    ImGui::SFML::Shutdown();
}