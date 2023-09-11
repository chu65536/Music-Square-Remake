#include "imgui.h"
#include "imgui-SFML.h"
#include "playstate.hpp"

#include <iostream>

PlayState::PlayState() = default;

State::Type PlayState::getType() const { return State::Type::Play; }

State::Type PlayState::update() {
    if (ImGui::Button("Menu", ImVec2(300.f, 100.f)))
        return State::Type::Menu;

    return State::Type::Play;
}

void PlayState::render(sf::RenderWindow& window) {
    std::cout << "rendering play!" << std::endl;
    window.clear(); 
    ImGui::SFML::Render(window);
    window.display();
}
