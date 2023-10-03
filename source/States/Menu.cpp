#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Menu.hpp"
#include <iostream> 


Menu::Menu(const InterfaceData& interfaceData) :
    m_interfaceData(interfaceData) {}

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
    State::Type returnValue = mainMenu();

    return returnValue;
}

void Menu::Render(sf::RenderWindow& window) {
}

State::Type Menu::mainMenu() {
    State::Type returnValue = State::Type::None;

    size_t buttonsCnt = 4; 
    ImVec2 m_windowpos;
    m_windowpos.x = m_interfaceData.workPos.x + 100.f;
    m_windowpos.y = m_interfaceData.workPos.y + m_interfaceData.workSize.y / 2 - m_interfaceData.menuBtnSz.y * buttonsCnt / 2;
    ImGui::SetNextWindowPos(m_windowpos, ImGuiCond_Always, m_interfaceData.workPosPivot);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

    ImGui::PushStyleColor(ImGuiCol_Button, m_interfaceData.frontColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_interfaceData.hoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_interfaceData.clickedColor);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[6]);
    ImGui::Begin("Main Menu", NULL, windowFlags);
    if (ImGui::Button("Songs", ImVec2(300.f, 100.f))) {
        returnValue = State::Type::SongSelection;
    }
    else if (ImGui::Button("Settings", ImVec2(300.f, 100.f))) {
        returnValue = State::Type::Settings;
    }
    else if (ImGui::Button("About", ImVec2(300.f, 100.f))) {
        returnValue = State::Type::About;
    }
    else if (ImGui::Button("Exit", ImVec2(300.f, 100.f))) {
        returnValue = State::Type::Exit;
    }

    ImGui::End();
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    return returnValue;
}
