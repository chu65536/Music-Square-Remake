#include "States/About.hpp"
#include "imgui.h"


void About::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::Escape:
            m_exit = true;
            break;
        }
    }
}

State::Type About::Update(const sf::Time& dt) {
    if (m_exit) {
        return State::Type::Menu;
    }
    ImGui::ShowDemoWindow();
    ImGui::Text("Text about this project...");
    return State::Type::None;
}

void About::Render(sf::RenderWindow& window) {
}