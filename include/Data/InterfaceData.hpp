#pragma once

#include <string>
#include "imgui.h"


class InterfaceData {
public:
    void Update();
    ImVec2 menuBtnSz {300.f ,100.f};
    ImVec2 selectionBtnSz {500.f, 75.f};
    ImVec2 workPos;
    ImVec2 workSize;
    ImVec2 workPosPivot {0.f, 0.f};
    ImVec4 frontColor {1.f, 1.f, 1.f, 0.f};
    ImVec4 hoveredColor {0.3f, 0.3f, 0.3f, 0.3f};
    ImVec4 clickedColor {0.6f, 0.6f, 0.6f, 0.3f};
private:
    ImGuiViewport* m_viewport;
};