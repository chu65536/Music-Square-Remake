#include "imgui.h"
#include "imgui-SFML.h"
#include "menustate.hpp"

#include <iostream>

MenuState::MenuState() = default;

State* MenuState::handleEvent(const sf::Event& event) {
    return nullptr;
}

void MenuState::update(sf::Time dt) {
}

void MenuState::render(sf::RenderWindow& window) {
    window.clear(); 
    ImGui::SFML::Render(window);
    window.display();
}
