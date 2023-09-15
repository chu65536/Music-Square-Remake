#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "playstate.hpp"


PlayState::PlayState(GameData& data) :
    gameData_(data),
    conductor_(data.music),
    map_(data.map),
    square_(data.square) {}

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

    if (conductor_.GetStatus() == sf::SoundSource::Playing) {
        timer_ += dt.asSeconds();
    }

    float dif = timer_ - conductor_.GetPlaybackPosition();
    if (abs(dif) > 0.1f) {
        timer_ = conductor_.GetPlaybackPosition();
    }

    Platform curPlatform = map_.GetNextPlatform(timer_);
    square_.Update(timer_, curPlatform);

    return State::Type::None;
}

void PlayState::Render(sf::RenderWindow& window) {
    sf::View camera(square_.GetPosition(), sf::Vector2f(500.f, 500.f));
    window.setView(camera);
    square_.Render(window);
    map_.Render(window);
}

