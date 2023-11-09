#include "States/Settings.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Tools/InterfaceTool.hpp"

Settings::Settings(SettingsData& settingsData, const InterfaceData& interfaceData) :
    m_settingsData(settingsData),
    m_interfaceData(interfaceData) 
{
}

void Settings::HandleEvents(sf::RenderWindow& window, sf::Event& event) 
{
    if (event.type == sf::Event::KeyPressed) 
    {
        sf::Keyboard::Key key = event.key.code;
        switch(key) 
        {
        case:: sf::Keyboard::Escape:
            m_exit = true;
            break;
        }
    }
}

State::Type Settings::Update(const sf::Time& dt) 
{
    State::Type returnValue = State::Type::None;
    returnValue = settingsMenu();
    if (m_exit) 
    {
        returnValue =  State::Type::Menu;
    }
    return returnValue;
}

void Settings::Render(sf::RenderWindow& window) 
{
}

State::Type Settings::settingsMenu() 
{
    State::Type returnValue = State::Type::None;

    float w = m_interfaceData.workSize.x / 3.f;
    float h = m_interfaceData.workSize.y / 12.f * 10.f;
    float x = m_interfaceData.workPos.x;
    float y = (m_interfaceData.workSize.y - h) * 0.5f;

    ITools::DefaultWindowBegin({x, m_interfaceData.workPos.y}, {w, m_interfaceData.workSize.y / 12.f}, 6, "Settings button");
    ITools::CenteredText("Settings");
    ITools::DefaultWindowEnd();

    ITools::DefaultWindowBegin({x, y}, {w, h}, 4, "Settings menu");
    ImGui::PushItemWidth(-FLT_MIN);
    // Square
    {   
        ITools::CenteredText("Square");

        ImGui::Text("Size"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::Checkbox("##Equal sides", &m_settingsData.equalSides); ImGui::SameLine();
        ImGui::DragInt2("##Square size", m_settingsData.squareSizeVector);  

        ImGui::Text("Speed"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::Checkbox("##Equal speeds", &m_settingsData.equalSpeeds); ImGui::SameLine();
        ImGui::DragInt2("##Square speed", m_settingsData.squareSpeedVector);  

        ImGui::Text("Outline thickness"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::DragInt("##Square outline thickness", &m_settingsData.squareOutlineThicknessVal);
        
        ImGui::Text("Color"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::ColorEdit3("##Square color", m_settingsData.squareColorVector, ImGuiColorEditFlags_NoInputs);
        ImGui::Text("Outline color"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::ColorEdit3("##Square outline color", m_settingsData.squareOutlineColorVector, ImGuiColorEditFlags_NoInputs);
    }

    // Platform;
    {   
        ImGui::NewLine();
        ITools::CenteredText("Platform");

        ImGui::Text("Visible"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::Checkbox("##Platform visibility", &m_settingsData.visiblePlatforms);

        ImGui::Text("Size"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::DragInt2("##Platform size", m_settingsData.platformSizeVector);

        ImGui::Text("Outline thickness"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::DragInt("##Platform outline thickness", &m_settingsData.platformOutlineThicknessVal);

        ImGui::Text("Color"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::ColorEdit3("##Platform color", m_settingsData.platformColorVector, ImGuiColorEditFlags_NoInputs);
        
        ImGui::Text("Outline color"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::ColorEdit3("##Platform outline color", m_settingsData.platformOutlineColorVector, ImGuiColorEditFlags_NoInputs);
    }

    // Background
    {
        ImGui::NewLine();
        ITools::CenteredText("Background");

        ImGui::Text("Color"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::ColorEdit3("##Background color", m_settingsData.backgroundColorVector, ImGuiColorEditFlags_NoInputs);
    }

    // Walls
    {   
        ImGui::NewLine();
        ITools::CenteredText("Walls");

        ImGui::Text("Outline Thickness"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);  
        ImGui::DragInt("##Walls outline thickness", &m_settingsData.wallsOutlineThicknessVal);

        ImGui::Text("Color"); ImGui::SameLine(); 
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::ColorEdit3("##Walls color", m_settingsData.wallsColorVector, ImGuiColorEditFlags_NoInputs);
        
        ImGui::Text("Outline Color"); ImGui::SameLine();
        ImGui::SetCursorPosX(w * 0.5f);
        ImGui::ColorEdit3("##Walls outline color", m_settingsData.wallsOutlineColorVector, ImGuiColorEditFlags_NoInputs);
    }
    ImGui::PopItemWidth();
    ITools::DefaultWindowEnd();

    ITools::DefaultWindowBegin({x, m_interfaceData.workSize.y / 12.f * 11.f}, {w, m_interfaceData.workSize.y / 12.f}, 6, "Back button");
    if (ImGui::Button("Back", {-FLT_MIN, -FLT_MIN}))
    {
        returnValue = State::Type::Menu;
    }
    ITools::DefaultWindowEnd();
    
    m_settingsData.Update();
    return returnValue;
}

