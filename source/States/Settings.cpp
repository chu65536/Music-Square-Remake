#include "States/Settings.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

Settings::Settings(GameData& data) :
    m_gameData(data) {    
}

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
    ImGui::InputFloat2("Square size", &m_gameData.squareSizeVector[0]);
    ImGui::InputFloat2("Square speed", &m_gameData.squareSpeedVector[0]);
    ImGui::InputFloat2("Platform size", &m_gameData.platformSizeVector[0]);
    ImGui::InputFloat2("Chunk size", &m_gameData.chunkSizeVector[0]);
    ImGui::ColorEdit3("Sqaure color", &m_gameData.squareColorVector[0]);
    ImGui::ColorEdit3("Walls color", &m_gameData.wallsColorVector[0]);
    ImGui::ColorEdit3("Background color", &m_gameData.backgroundColorVector[0]);
    m_gameData.Update();
}

