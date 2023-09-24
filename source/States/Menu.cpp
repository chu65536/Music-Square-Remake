#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Menu.hpp"


void Menu::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        }
    }
}

State::Type Menu::Update(const sf::Time& dt) {
    if (ImGui::Button("Songs")) {
        return State::Type::SongSelection;
    }
    if (ImGui::Button("Settings")) {
        return State::Type::Settings;
    }

    return State::Type::None;
}

void Menu::Render(sf::RenderWindow& window) {
}
