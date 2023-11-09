#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Menu.hpp"
#include "Tools/InterfaceTool.hpp"
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

void Menu::Render(sf::RenderWindow& window) 
{
}

State::Type Menu::mainMenu() 
{
    State::Type returnValue = State::Type::None;

    float w = m_interfaceData.workSize.x / 3.f;
    float h = m_interfaceData.workSize.y / 8.f * 6.f;
    float x = m_interfaceData.workPos.x;
    float y = (m_interfaceData.workSize.y - h) / 2.f;
    float btnY = h / 4.f;

    ITools::DefaultWindowBegin({x, y}, {w, h}, 5, "Menu");
    if (ImGui::Button("Songs", ImVec2(-FLT_MIN, btnY))) 
    {
        returnValue = State::Type::SongSelection;
    } else 
    if (ImGui::Button("Settings", ImVec2(-FLT_MIN, btnY))) 
    {
        returnValue = State::Type::Settings;
    } else 
    if (ImGui::Button("About", ImVec2(-FLT_MIN, btnY))) 
    {
        returnValue = State::Type::About;
    } else 
    if (ImGui::Button("Exit", ImVec2(-FLT_MIN, btnY))) 
    {
        returnValue = State::Type::Exit;
    }
    ITools::DefaultWindowEnd();

    return returnValue;
}
