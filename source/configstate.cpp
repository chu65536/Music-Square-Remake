#include "configstate.hpp"

ConfigState::ConfigState(ConfigData& data) :
    configData_(data) {}

void ConfigState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case:: sf::Keyboard::Escape:
            exit_ = true;
            break;
        }
    }
}

State::Type ConfigState::Update(sf::Time dt) {
    if (exit_) {
        return State::Type::Menu;
    }

    configMenu();

    return State::Type::None;
}

void ConfigState::Render(sf::RenderWindow& window) {
}

void ConfigState::configMenu() {
    
}

