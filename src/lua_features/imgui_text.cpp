#include <tuple>
#include <string_view>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_text(sol::table& imgui)
{
    imgui.set_function("TextUnformatted", [](std::string_view text) -> void { ImGui::TextUnformatted(text.data(), text.data() + text.size()); });
    imgui.set_function("Text", [](std::string_view text) -> void { ImGui::Text("%s", text.data()); });
    imgui.set_function("TextColored", [](float colr, float colg, float colb, float cola, std::string_view text) -> void { ImGui::TextColored({colr, colg, colb, cola}, "%s", text.data()); });
    imgui.set_function("TextDisabled", [](std::string_view text) -> void { ImGui::TextDisabled("%s", text.data()); });
    imgui.set_function("TextWrapped", [](std::string_view text) -> void { ImGui::TextWrapped("%s", text.data()); });
    imgui.set_function("LabelText", [](std::string_view label, std::string_view text) -> void { ImGui::LabelText(label.data(), "%s", text.data()); });
    imgui.set_function("BulletText", [](std::string_view text) -> void { ImGui::BulletText("%s", text.data()); });
}
