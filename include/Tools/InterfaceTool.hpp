#include <string>
#include "imgui.h"
#include "imgui-SFML.h"


namespace ITools {
void CenteredText(const std::string& text);
void DefaultWindowBegin(ImVec2 pos, ImVec2 sz, unsigned int fontSz, const std::string& title);
void DefaultWindowEnd();
}