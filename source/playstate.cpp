#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "playstate.hpp"


PlayState::PlayState(GameData& gameData, ConfigData& configData) :
    gameData_(gameData),
    configData_(configData),
    conductor_(gameData.music),
    camera_(gameData.windowPt, gameData.square, configData.position, configData.windowSize) {
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

    if (event.type == sf::Event::MouseWheelScrolled) {
        float delta = event.mouseWheelScroll.delta * 0.1f;
        if (0.2f < camera_.zoom + delta && camera_.zoom + delta < 5.f) {
            camera_.zoom += delta;
        }
    }
}

State::Type PlayState::Update(sf::Time dt) {
    if (exit_) {
        gameData_.Clear();
        return State::Type::Menu;
    }

    settingsWindow();
    if (!gameData_.map.isEnd() && conductor_.GetStatus() == sf::SoundSource::Playing) {
        timer_ += dt.asSeconds();
        conductor_.Normalize(timer_);
    }
    if (gameData_.map.isEnd()) {
        timer_ = gameData_.map.GetNextPlatform(timer_).GetTime();
    }
    Platform curPlatform = gameData_.map.GetNextPlatform(timer_);
    gameData_.square.Update(timer_, curPlatform);
    camera_.Update(dt);

    return State::Type::None;
}

void PlayState::Render(sf::RenderWindow& window) {
    gameData_.map.Render(window, camera_);
    gameData_.square.Render(window);
}

void PlayState::settingsWindow() {
    if (ImGui::Begin("Live Settings")) {
        ImGui::DragFloat("Camera zoom", &camera_.zoom, 0.1f, 0.1f, 5.f);
        ImGui::DragFloat("Camera speed", &camera_.speed, 0.2f, 1.f, 10.f);
    }
    ImGui::End();
}

