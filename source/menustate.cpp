#include "imgui.h"
#include "imgui-SFML.h"
#include "menustate.hpp"

#include <iostream>

MenuState::MenuState() = default;

State::Type MenuState::getType() const { return State::Type::Menu; }

State::Type MenuState::update() {
    if (ImGui::Button("Play", ImVec2(300.f, 100.f)))
        return State::Type::Play;

    return State::Type::Menu;
}

void MenuState::render(sf::RenderWindow& window) {
    std::cout << "rendering menu!" << std::endl;
    window.clear(); 
    ImGui::SFML::Render(window);
    window.display();
}
