#include "States/Settings.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

Settings::Settings(UserData& data) :
    m_userData(data) {}

void Settings::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case:: sf::Keyboard::Escape:
            m_exit = true;
            break;
        }
    }
}

State::Type Settings::Update(const sf::Time& dt) {
    if (m_exit) {
        return State::Type::Menu;
    }

    configMenu();

    return State::Type::None;
}

void Settings::Render(sf::RenderWindow& window) {
}

void Settings::configMenu() {
    ImGui::ShowDemoWindow();
    ImGui::Checkbox("Debug info", &m_userData.debugWindow);
    ImGui::ColorEdit3("Sqaure color", &m_userData.squareColorVector[0]);
    ImGui::ColorEdit3("Walls color", &m_userData.wallsColorVector[0]);
    ImGui::ColorEdit3("Background color", &m_userData.backgroundColorVector[0]);
    m_userData.Update();
}

