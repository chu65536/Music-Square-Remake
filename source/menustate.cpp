#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "menustate.hpp"


void MenuState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        }
    }
}

State::Type MenuState::Update(sf::Time dt) {
    if (ImGui::Button("Songs")) {
        return State::Type::Selection;
    }
    if (ImGui::Button("Settings")) {
        return State::Type::Config;
    }

    return State::Type::None;
}

void MenuState::Render(sf::RenderWindow& window) {
}
