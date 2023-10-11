#include "States/Settings.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tools/InterfaceTool.hpp"

Settings::Settings(SettingsData& settingsData, const InterfaceData& interfaceData) :
    m_settingsData(settingsData),
    m_interfaceData(interfaceData) {}

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
    State::Type returnValue = State::Type::None;
    returnValue = settingsMenu();
    if (m_exit) {
        returnValue =  State::Type::Menu;
    }
    return returnValue;
}

void Settings::Render(sf::RenderWindow& window) {
}

State::Type Settings::settingsMenu() {
    ImVec2 windowPosition, windowSize;
    windowPosition.x = m_interfaceData.workPos.x;
    windowPosition.y = m_interfaceData.workPos.y;
    windowSize.x = m_interfaceData.workSize.x / 3.f;
    windowSize.y = m_interfaceData.workSize.y / 10.f * 9.f;
    ImGui::SetNextWindowPos(windowPosition, ImGuiCond_Always, m_interfaceData.workPosPivot);
    ImGui::SetNextWindowSize(windowSize);
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;


    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.8f, 0.8f, 0.8f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[3]);
    if (ImGui::Begin("Settings menu", NULL, windowFlags)) {
        ImGui::PushItemWidth(-FLT_MIN);

        // Square
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[5]);
        ITools::CenteredText("Square");
        ImGui::PopFont();
        { 
            // Square size 
            ITools::CenteredText("Size");
            ImGui::Checkbox("##Equal sides", &m_settingsData.equalSides); ImGui::SameLine();
            ImGui::SliderInt2("##Square size", m_settingsData.squareSizeVector, 10, 100);  
        }
        {
            // Square speed
            ITools::CenteredText("Speed");
            ImGui::Checkbox("##Equal speed", &m_settingsData.equalSpeeds); ImGui::SameLine();
            ImGui::SliderInt2("##Square speed", m_settingsData.squareSpeedVector, 100, 1000); 
        }
        {
            // Square color
            ITools::CenteredText("Color");   
            ImGui::ColorEdit3("##Square color", &m_settingsData.squareColorVector[0]);
        }
        {   
            // Square outline thickness
            ITools::CenteredText("Outline Thickness");   
            ImGui::SliderInt("##Square outline thickness", &m_settingsData.squareOutlineThicknessVal, 0, std::min(m_settingsData.squareSize.x, m_settingsData.squareSize.y) / 2);
        }
        {
            // Square outline color
            ITools::CenteredText("Outline Color");   
            ImGui::ColorEdit3("##Square outline color", &m_settingsData.squareOutlineColorVector[0]);  
        }
        ImGui::Separator();

        // Platform;
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[5]);
        ITools::CenteredText("Platform");
        ImGui::PopFont();
        {   
            // Platform size
            ITools::CenteredText("Size");
            ImGui::SliderInt2("##Platform size", m_settingsData.platformSizeVector, 10, 100);   
        }
        {
            // Platform color
            ITools::CenteredText("Color");
            ImGui::ColorEdit3("##Platform color", &m_settingsData.platformColorVector[0]);
        }
        {
            // Platform outline thickness
            ITools::CenteredText("Outline Thickness");   
            ImGui::SliderInt("##Platform outline thickness", &m_settingsData.platformOutlineThicknessVal, 0, std::min(m_settingsData.platformSize.x, m_settingsData.platformSize.y) / 2);
        }
        {
            // Platform outline color
            ITools::CenteredText("Outline Color");
            ImGui::ColorEdit3("##Platform outline color", &m_settingsData.platformOutlineColorVector[0]);
        }
        ImGui::Separator();

        // Background
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[5]);
        ITools::CenteredText("Background");
        ImGui::PopFont();
        {
            // Background color
            ITools::CenteredText("Color");
            ImGui::ColorEdit3("##Background color", &m_settingsData.backgroundColorVector[0]);
        }
        ImGui::Separator();

        // Walls
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[5]);
        ITools::CenteredText("Walls");
        ImGui::PopFont();
        {
            // Walls color
            ITools::CenteredText("Color");
            ImGui::ColorEdit3("##Walls color", &m_settingsData.wallsColorVector[0]);
        }
        {
            // Walls outline thickness
            ITools::CenteredText("Outline Thickness");   
            ImGui::SliderInt("##Walls outline thickness", &m_settingsData.wallsOutlineThicknessVal, 0, 20);
        }
        {
            // Walls outline color
            ITools::CenteredText("Outline Color");
            ImGui::ColorEdit3("##Walls outline color", &m_settingsData.wallsOutlineColorVector[0]);
        }
        ImGui::PopItemWidth();
    }
    ImGui::End();

    // Back button
    ImVec2 buttonSize(windowSize.x, m_interfaceData.workSize.y / 10.f);
    ImVec2 buttonPosition(windowPosition.x, windowSize.y);
    ImGui::SetNextWindowPos(buttonPosition);
    ImGui::SetNextWindowSize(buttonSize);
    ImGui::PushStyleColor(ImGuiCol_Button, m_interfaceData.frontColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_interfaceData.hoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_interfaceData.clickedColor);
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[6]);
    State::Type returnValue = State::Type::None;
    if (ImGui::Begin("Back button", NULL, windowFlags)) {
        if (ImGui::Button("Back", ImVec2(-FLT_MIN, -FLT_MIN))) {
            returnValue = State::Type::Menu;
        }
    }
    ImGui::PopFont();
    ImGui::End();
    ImGui::PopFont();
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(7);
    
    m_settingsData.Update();
    return returnValue;
}

