#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "playstate.hpp"


PlayState::PlayState(GameData& gameData, ConfigData& configData) :
    gameData_(gameData),
    configData_(configData),
    conductor_(gameData.music) {
    srand(time(0));
}

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
        case:: sf::Keyboard::Escape:
            exit_ = true;
            break;
        }
    }
}

State::Type PlayState::Update(sf::Time dt) {
    if (exit_) {
        gameData_.Clear();
        return State::Type::Menu;
    }

    settingsWindow();
    if (!gameData_.map.isEnd()) {
        if (conductor_.GetStatus() == sf::SoundSource::Playing) {
            timer_ += dt.asSeconds();
        }

        float dif = timer_ - conductor_.GetPlaybackPosition();
        if (abs(dif) > 0.1f) {
            timer_ = conductor_.GetPlaybackPosition();
        }
    }
    Platform curPlatform = gameData_.map.GetNextPlatform(timer_);
    gameData_.square.Update(timer_, curPlatform);
    gameData_.camera.Update(dt);

    return State::Type::None;
}

void PlayState::Render(sf::RenderWindow& window) {
    gameData_.map.Render(window);
    gameData_.square.Render(window);
}

void PlayState::settingsWindow() {
    if (ImGui::Begin("Live Settings")) {
        ImGui::DragFloat("Camera zoom", &gameData_.camera.zoom, 0.05f, 0.1f, 1.f);
        ImGui::DragFloat("Camera speed", &gameData_.camera.speed, 0.2f, 1.f, 10.f);
    }
    ImGui::End();
}

