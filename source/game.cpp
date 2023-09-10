#include <iostream>
#include "game.hpp"
#include "menustate.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

Game::Game() {
    window_.create(sf::VideoMode(500u, 500u), "Title");
    window_.setKeyRepeatEnabled(false);
    ImGui::SFML::Init(window_);
    conductor_.Init();
    currentState_ = new MenuState();
}

void Game::Run() {
    sf::Clock clock;
    while (window_.isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart();
        while (window_.pollEvent(event)) {
            State* nextState = currentState_->handleEvent(event);
            ImGui::SFML::ProcessEvent(window_, event);
            if (nextState) {
                delete currentState_;
                currentState_ = nextState;
            }

            if (event.type == sf::Event::Closed) {
                window_.close();
            }
        }
        ImGui::SFML::Update(window_, deltaTime);
        currentState_->update(deltaTime);
        currentState_->render(window_);
    }

    ImGui::SFML::Shutdown();
}