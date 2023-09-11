#include "imgui.h"
#include "imgui-SFML.h"
#include "playstate.hpp"

#include <iostream>

PlayState::PlayState() {
    conductor_.Init();
}

State::Type PlayState::GetType() const { return State::Type::Play; }

void PlayState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::Space:
            if (conductor_.GetStatus() != sf::SoundSource::Playing) {
                conductor_.Play();
            }
            else {
                conductor_.Pause();
            }
            break;
        case sf::Keyboard::S:
            conductor_.Stop();
            break;
        }
    }
}

State::Type PlayState::Update() {
    if (ImGui::Button("Menu", ImVec2(300.f, 100.f)))
        return State::Type::Menu;

    return State::Type::Play;
}

void PlayState::Render(sf::RenderWindow& window) {
    window.clear(); 
    ImGui::SFML::Render(window);
    window.display();
}
