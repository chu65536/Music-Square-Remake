#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "playstate.hpp"


PlayState::PlayState(GameData& data) :
    gameData_(data),
    conductor_(data.music) {}

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

State::Type PlayState::Update(sf::Time dt) {
    ImGui::ShowDemoWindow();

    if (ImGui::Button("Menu", ImVec2(300.f, 100.f))){
        gameData_.music.stop();
        return State::Type::Menu;
    }

    return State::Type::None;
}

void PlayState::Render(sf::RenderWindow& window) {
}
