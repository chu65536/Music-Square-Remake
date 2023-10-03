#include "Data/InterfaceData.hpp"


void InterfaceData::Update() {
    m_viewport = ImGui::GetMainViewport();
    workPos = m_viewport->WorkPos;
    workSize = m_viewport->WorkSize;
}
