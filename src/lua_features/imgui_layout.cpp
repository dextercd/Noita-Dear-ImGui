#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_layout(sol::table& imgui)
{
    imgui.set_function("Separator", sol::resolve<void()>(ImGui::Separator));
    imgui.set_function("SameLine",
        sol::overload(
            []() { return ImGui::SameLine(); },
            [](float offset_from_start_x) { return ImGui::SameLine(offset_from_start_x); },
            [](float offset_from_start_x, float spacing) { return ImGui::SameLine(offset_from_start_x, spacing); }));
    imgui.set_function("NewLine", sol::resolve<void()>(ImGui::NewLine));
    imgui.set_function("Spacing", sol::resolve<void()>(ImGui::Spacing));
    imgui.set_function("Dummy", [](float size_x, float size_y) { return ImGui::Dummy({size_x, size_y}); });
    imgui.set_function("Indent", sol::overload([]() { return ImGui::Indent(); }, ImGui::Indent));
    imgui.set_function("Unindent", sol::overload([]() { return ImGui::Unindent(); }, ImGui::Unindent));
    imgui.set_function("BeginGroup", sol::resolve<void()>(ImGui::BeginGroup));
    imgui.set_function("EndGroup", sol::resolve<void()>(ImGui::EndGroup));
    imgui.set_function("GetCursorPos", []() { auto ret = ImGui::GetCursorPos(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("GetCursorPosX", []() { return ImGui::GetCursorPosX(); });
    imgui.set_function("GetCursorPosY", []() { return ImGui::GetCursorPosY(); });
    imgui.set_function("SetCursorPos",
        [](float local_pos_x, float local_pos_y) { return ImGui::SetCursorPos({local_pos_x, local_pos_y}); });
    imgui.set_function("SetCursorPosX", sol::resolve<void(float)>(ImGui::SetCursorPosX));
    imgui.set_function("SetCursorPosY", sol::resolve<void(float)>(ImGui::SetCursorPosY));
    imgui.set_function("GetCursorStartPos", []() { auto ret = ImGui::GetCursorStartPos(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("GetCursorScreenPos", []() { auto ret = ImGui::GetCursorScreenPos(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("SetCursorScreenPos", [](float size_x, float size_y) { return ImGui::SetCursorScreenPos({size_x, size_y}); });
    imgui.set_function("AlignTextToFramePadding", sol::resolve<void()>(ImGui::AlignTextToFramePadding));
    imgui.set_function("GetTextLineHeight", sol::resolve<float()>(ImGui::GetTextLineHeight));
    imgui.set_function("GetTextLineHeightWithSpacing", sol::resolve<float()>(ImGui::GetTextLineHeightWithSpacing));
    imgui.set_function("GetFrameHeight", sol::resolve<float()>(ImGui::GetFrameHeight));
    imgui.set_function("GetFrameHeightWithSpacing", sol::resolve<float()>(ImGui::GetFrameHeightWithSpacing));
}
