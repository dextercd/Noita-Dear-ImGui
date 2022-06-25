#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_layout(sol::table& imgui)
{
    imgui.set_function("Separator", ImGui::Separator);
    imgui.set_function("SameLine",
        sol::overload(
            []() { return ImGui::SameLine(); },
            [](float offset_from_start_x) { return ImGui::SameLine(offset_from_start_x); },
            [](float offset_from_start_x, float spacing) { return ImGui::SameLine(offset_from_start_x, spacing); }));
    imgui.set_function("NewLine", ImGui::NewLine);
    imgui.set_function("Spacing", ImGui::Spacing);
    imgui.set_function("Dummy", [](float size_x, float size_y) { return ImGui::Dummy({size_x, size_y}); });
    imgui.set_function("Indent", sol::overload([]() { return ImGui::Indent(); }, ImGui::Indent));
    imgui.set_function("Unindent", sol::overload([]() { return ImGui::Unindent(); }, ImGui::Unindent));
    imgui.set_function("BeginGroup", ImGui::BeginGroup);
    imgui.set_function("EndGroup", ImGui::EndGroup);
    imgui.set_function("GetCursorPos", []() { auto ret = ImGui::GetCursorPos(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("GetCursorPosX", []() { return ImGui::GetCursorPosX(); });
    imgui.set_function("GetCursorPosY", []() { return ImGui::GetCursorPosY(); });
    imgui.set_function("SetCursorPos",
        [](float local_pos_x, float local_pos_y) { return ImGui::SetCursorPos({local_pos_x, local_pos_y}); });
    imgui.set_function("SetCursorPosX", ImGui::SetCursorPosX);
    imgui.set_function("SetCursorPosY", ImGui::SetCursorPosY);
    imgui.set_function("GetCursorStartPos", []() { auto ret = ImGui::GetCursorStartPos(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("GetCursorScreenPos", []() { auto ret = ImGui::GetCursorScreenPos(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("SetCursorScreenPos", [](float size_x, float size_y) { return ImGui::SetCursorScreenPos({size_x, size_y}); });
    imgui.set_function("AlignTextToFramePadding", ImGui::AlignTextToFramePadding);
    imgui.set_function("GetTextLineHeight", ImGui::GetTextLineHeight);
    imgui.set_function("GetTextLineHeightWithSpacing", ImGui::GetTextLineHeightWithSpacing);
    imgui.set_function("GetFrameHeight", ImGui::GetFrameHeight);
    imgui.set_function("GetFrameHeightWithSpacing", ImGui::GetFrameHeightWithSpacing);
}
