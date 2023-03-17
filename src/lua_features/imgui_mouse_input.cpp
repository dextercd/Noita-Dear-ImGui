#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_mouse_input(sol::table& imgui)
{
    imgui.new_enum("MouseButton",
        "Left",   ImGuiMouseButton_Left,
        "Right",  ImGuiMouseButton_Right,
        "Middle", ImGuiMouseButton_Middle,
        "COUNT",  ImGuiMouseButton_COUNT
    );

    imgui.set_function("IsMouseDown", sol::resolve<bool(ImGuiMouseButton)>(ImGui::IsMouseDown));
    imgui.set_function("IsMouseClicked",
        sol::overload(
            [](ImGuiMouseButton button) { return ImGui::IsMouseClicked(button); },
            sol::resolve<bool(ImGuiMouseButton, bool)>(ImGui::IsMouseClicked)));
    imgui.set_function("IsMouseReleased", sol::resolve<bool(ImGuiMouseButton)>(ImGui::IsMouseReleased));
    imgui.set_function("IsMouseDoubleClicked", sol::resolve<bool(ImGuiMouseButton)>(ImGui::IsMouseDoubleClicked));
    imgui.set_function("GetMouseClickedCount", sol::resolve<int(ImGuiMouseButton)>(ImGui::GetMouseClickedCount));
    imgui.set_function("IsMousePosValid",
        sol::overload(
            []() -> bool { return ImGui::IsMousePosValid(); },
            [](float posx, float posy) { ImVec2 pos{posx, posy}; return ImGui::IsMousePosValid(&pos); }));

    imgui.set_function("GetMousePos",
        []() -> std::tuple<float, float> { auto ret = ImGui::GetMousePos(); return std::tuple{ret.x, ret.y}; });

    imgui.set_function("GetMousePosOnOpeningCurrentPopup",
        []() -> std::tuple<float, float> { auto ret = ImGui::GetMousePosOnOpeningCurrentPopup(); return std::tuple{ret.x, ret.y}; });

    imgui.set_function("IsMouseDragging",
        sol::overload(
            [](ImGuiMouseButton button) { return ImGui::IsMouseDragging(button); },
            sol::resolve<bool(ImGuiMouseButton, float)>(ImGui::IsMouseDragging)));
    imgui.set_function("GetMouseDragDelta",
        sol::overload(
            []() -> std::tuple<float, float> { auto ret = ImGui::GetMouseDragDelta(); return std::tuple{ret.x, ret.y}; },
            [](ImGuiMouseButton button) { auto ret = ImGui::GetMouseDragDelta(button); return std::tuple{ret.x, ret.y}; },
            [](ImGuiMouseButton button, float lock_threshold) { auto ret = ImGui::GetMouseDragDelta(button, lock_threshold); return std::tuple{ret.x, ret.y}; }));
    imgui.set_function("ResetMouseDragDelta",
        sol::overload(
            []() -> void { return ImGui::ResetMouseDragDelta(); },
            sol::resolve<void(ImGuiMouseButton)>(ImGui::ResetMouseDragDelta)));

    imgui.new_enum("MouseCursor",
        "None",       ImGuiMouseCursor_None,
        "Arrow",      ImGuiMouseCursor_Arrow,
        "TextInput",  ImGuiMouseCursor_TextInput,
        "ResizeAll",  ImGuiMouseCursor_ResizeAll,
        "ResizeNS",   ImGuiMouseCursor_ResizeNS,
        "ResizeEW",   ImGuiMouseCursor_ResizeEW,
        "ResizeNESW", ImGuiMouseCursor_ResizeNESW,
        "ResizeNWSE", ImGuiMouseCursor_ResizeNWSE,
        "Hand",       ImGuiMouseCursor_Hand,
        "NotAllowed", ImGuiMouseCursor_NotAllowed,
        "COUNT",      ImGuiMouseCursor_COUNT
    );

    imgui.set_function("GetMouseCursor", sol::resolve<ImGuiMouseCursor()>(ImGui::GetMouseCursor));
    imgui.set_function("SetMouseCursor", sol::resolve<void(ImGuiMouseCursor)>(ImGui::SetMouseCursor));
    imgui.set_function("SetNextFrameWantCaptureMouse", sol::resolve<void(bool)>(ImGui::SetNextFrameWantCaptureMouse));
}
