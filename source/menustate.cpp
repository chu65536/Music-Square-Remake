#include "imgui.h"
#include "imgui-SFML.h"
#include "menustate.hpp"

#include <iostream>

MenuState::MenuState() = default;

State::Type MenuState::GetType() const { return State::Type::Menu; }

void MenuState::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
}

State::Type MenuState::Update() {
    if (ImGui::Button("Play", ImVec2(300.f, 100.f)))
        return State::Type::Play;

    return State::Type::Menu;
}

void MenuState::Render(sf::RenderWindow& window) {
    window.clear(); 
    ImGui::SFML::Render(window);
    window.display();
}
