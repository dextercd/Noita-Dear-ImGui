#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_text(sol::table& imgui)
{
    imgui.set_function("Text", [](const char* text) { ImGui::Text("%s", text); });
    imgui.set_function("TextColored", [](ImVec4 col, const char* text) { ImGui::TextColored(col, "%s", text); });
    imgui.set_function("TextDisabled", [](const char* text) { ImGui::TextDisabled("%s", text); });
    imgui.set_function("TextWrapped", [](const char* text) { ImGui::TextWrapped("%s", text); });
    imgui.set_function("LabelText", [](const char* label, const char* text) { ImGui::LabelText(label, "%s", text); });
    imgui.set_function("BulletText", [](const char* text) { ImGui::BulletText("%s", text); });
}
