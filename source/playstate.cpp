#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "playstate.hpp"
#include "map.hpp"


PlayState::PlayState(GameData& data) :
    gameData_(data),
    conductor_(data.music),
    map_(data.map) {}

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
        gameData_.music.stop();
        return State::Type::Menu;
    }

    return State::Type::None;
}

void PlayState::Render(sf::RenderWindow& window) {
    map_.Render(window);
}
