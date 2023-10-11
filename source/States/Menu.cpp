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

    ImVec2 windowPosition, windowSize;
    windowSize.x = m_interfaceData.workSize.x / 3.f;
    windowSize.y = m_interfaceData.workSize.y / 8.f * 6.f;
    windowPosition.x = m_interfaceData.workPos.x;
    windowPosition.y = m_interfaceData.workSize.y / 8.f;
    ImGui::SetNextWindowPos(windowPosition, ImGuiCond_Always, m_interfaceData.workPosPivot);
    ImGui::SetNextWindowSize(windowSize);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_Button, m_interfaceData.frontColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_interfaceData.hoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_interfaceData.clickedColor);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[6]);
    ImGui::Begin("Main Menu", NULL, windowFlags);
    if (ImGui::Button("Songs", ImVec2(-FLT_MIN, windowSize.y / 4.f))) {
        returnValue = State::Type::SongSelection;
    }
    else if (ImGui::Button("Settings", ImVec2(-FLT_MIN, windowSize.y / 4.f))) {
        returnValue = State::Type::Settings;
    }
    else if (ImGui::Button("About", ImVec2(-FLT_MIN, windowSize.y / 4.f))) {
        returnValue = State::Type::About;
    }
    else if (ImGui::Button("Exit", ImVec2(-FLT_MIN, windowSize.y / 4.f))) {
        returnValue = State::Type::Exit;
    }

    ImGui::End();
    ImGui::PopFont();
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(3);
    return returnValue;
}
