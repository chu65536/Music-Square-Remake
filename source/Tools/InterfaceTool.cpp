#include "Tools/InterfaceTool.hpp"
#include <iostream>

namespace ITools 
{
void DefaultWindowBegin(ImVec2 pos, ImVec2 sz, unsigned int fontSz, const std::string& title)
{
    // Default values
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

    ImVec4 backgroundColor(0.1f, 0.1f, 0.1f, 1.f);
    ImVec4 buttonColor(0.1f, 0.1f, 0.1f, 1.f);
    ImVec4 buttonHoveredColor(0.3f, 0.3f, 0.3f, 1.f);
    ImVec4 buttonClickedColor(0.6f, 0.6f, 0.6f, 1.f);
    
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always, {0, 0});
    ImGui::SetNextWindowSize(sz);

    // Style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));

    // Color
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonHoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonClickedColor);

    ImGui::PushStyleColor(ImGuiCol_FrameBg, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, buttonHoveredColor);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, buttonClickedColor);

    ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, buttonClickedColor);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);

    // Font
    assert(fontSz < ImGui::GetIO().Fonts->Fonts.size() && "Font id is out of range");
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[fontSz]);

    // Begin
    ImGui::Begin(title.c_str(), NULL, windowFlags);
}

void DefaultWindowEnd()
{
    ImGui::End();
    ImGui::PopFont();
    ImGui::PopStyleVar(3);   
    ImGui::PopStyleColor(8);
}

void CenteredText(const std::string& text) 
{
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth   = ImGui::CalcTextSize(text.c_str()).x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text.c_str());
}
}