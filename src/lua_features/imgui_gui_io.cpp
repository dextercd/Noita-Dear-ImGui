#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_gui_io(sol::table& imgui)
{
    imgui.new_usertype<ImGuiIO>("GuiIO", sol::no_constructor,
        "ConfigFlags", &ImGuiIO::ConfigFlags,
        "BackendFlags", &ImGuiIO::BackendFlags,
        "DisplaySize", &ImGuiIO::DisplaySize,
        "DeltaTime", &ImGuiIO::DeltaTime,
        "IniSavingRate", &ImGuiIO::IniSavingRate,
        "IniFilename", &ImGuiIO::IniFilename,
        "LogFilename", &ImGuiIO::LogFilename,
        "MouseDoubleClickTime", &ImGuiIO::MouseDoubleClickTime,
        "MouseDoubleClickMaxDist", &ImGuiIO::MouseDoubleClickMaxDist,
        "MouseDragThreshold", &ImGuiIO::MouseDragThreshold,
        "KeyRepeatDelay", &ImGuiIO::KeyRepeatDelay,
        "KeyRepeatRate", &ImGuiIO::KeyRepeatRate,
        // "UserData", &ImGuiIO::UserData,
        // "Fonts", &ImGuiIO::Fonts,
        "FontGlobalScale", &ImGuiIO::FontGlobalScale,
        "FontAllowUserScaling", &ImGuiIO::FontAllowUserScaling,
        "FontDefault", &ImGuiIO::FontDefault,
        "DisplayFramebufferScale", &ImGuiIO::DisplayFramebufferScale,
        "MouseDrawCursor", &ImGuiIO::MouseDrawCursor,
        "ConfigMacOSXBehaviors", &ImGuiIO::ConfigMacOSXBehaviors,
        "ConfigInputTrickleEventQueue", &ImGuiIO::ConfigInputTrickleEventQueue,
        "ConfigInputTextCursorBlink", &ImGuiIO::ConfigInputTextCursorBlink,
        "ConfigDragClickToInputText", &ImGuiIO::ConfigDragClickToInputText,
        "ConfigWindowsResizeFromEdges", &ImGuiIO::ConfigWindowsResizeFromEdges,
        "ConfigWindowsMoveFromTitleBarOnly", &ImGuiIO::ConfigWindowsMoveFromTitleBarOnly,
        "ConfigMemoryCompactTimer", &ImGuiIO::ConfigMemoryCompactTimer,
        "BackendPlatformName", sol::readonly(&ImGuiIO::BackendPlatformName),
        "BackendRendererName", sol::readonly(&ImGuiIO::BackendRendererName),
        // "ClipboardUserData", &ImGuiIO::ClipboardUserData,
        // const char* (*GetClipboardTextFn)(void* user_data);
        // void        (*SetClipboardTextFn)(void* user_data, const char* text);
        // void        (*SetPlatformImeDataFn)(ImGuiViewport* viewport, ImGuiPlatformImeData* data);

        "AddKeyEvent", &ImGuiIO::AddKeyEvent,
        "AddKeyAnalogEvent", &ImGuiIO::AddKeyAnalogEvent,
        "AddMousePosEvent", &ImGuiIO::AddMousePosEvent,
        "AddMouseButtonEvent", &ImGuiIO::AddMouseButtonEvent,
        "AddMouseWheelEvent", &ImGuiIO::AddMouseWheelEvent,
        "AddFocusEvent", &ImGuiIO::AddFocusEvent,
        "AddInputCharacter", &ImGuiIO::AddInputCharacter,
        "AddInputCharacterUTF16", &ImGuiIO::AddInputCharacterUTF16,
        "AddInputCharactersUTF8", &ImGuiIO::AddInputCharactersUTF8,
        "SetKeyEventNativeData", &ImGuiIO::SetKeyEventNativeData,
        "SetAppAcceptingEvents", &ImGuiIO::SetAppAcceptingEvents,

        "WantCaptureMouse", sol::readonly(&ImGuiIO::WantCaptureMouse),
        "WantCaptureKeyboard", sol::readonly(&ImGuiIO::WantCaptureKeyboard),
        "WantTextInput", sol::readonly(&ImGuiIO::WantTextInput),
        "WantSetMousePos", sol::readonly(&ImGuiIO::WantSetMousePos),
        "WantSaveIniSettings", sol::readonly(&ImGuiIO::WantSaveIniSettings),
        "NavActive", sol::readonly(&ImGuiIO::NavActive),
        "NavVisible", sol::readonly(&ImGuiIO::NavVisible),
        "Framerate", sol::readonly(&ImGuiIO::Framerate),
        "MetricsRenderVertices", sol::readonly(&ImGuiIO::MetricsRenderVertices),
        "MetricsRenderIndices", sol::readonly(&ImGuiIO::MetricsRenderIndices),
        "MetricsRenderWindows", sol::readonly(&ImGuiIO::MetricsRenderWindows),
        "MetricsActiveWindows", sol::readonly(&ImGuiIO::MetricsActiveWindows),
        "MetricsActiveAllocations", sol::readonly(&ImGuiIO::MetricsActiveAllocations),
        "MouseDelta", sol::readonly(&ImGuiIO::MouseDelta)
    );

    imgui.set_function("GetIO", []() { return &ImGui::GetIO(); });

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
            []() { return ImGui::IsMousePosValid(); },
            [](float posx, float posy) { ImVec2 pos{posx, posy}; return ImGui::IsMousePosValid(&pos); }));
    imgui.set_function("GetMousePos", []() { auto ret = ImGui::GetMousePos(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("GetMousePosOnOpeningCurrentPopup", []() { auto ret = ImGui::GetMousePosOnOpeningCurrentPopup(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("IsMouseDragging",
        sol::overload(
            [](ImGuiMouseButton button) { return ImGui::IsMouseDragging(button); },
            sol::resolve<bool(ImGuiMouseButton, float)>(ImGui::IsMouseDragging)));
    imgui.set_function("GetMouseDragDelta",
        sol::overload(
            []() { auto ret = ImGui::GetMouseDragDelta(); return std::tuple{ret.x, ret.y}; },
            [](ImGuiMouseButton button) { auto ret = ImGui::GetMouseDragDelta(button); return std::tuple{ret.x, ret.y}; },
            [](ImGuiMouseButton button, float lock_threshold) { auto ret = ImGui::GetMouseDragDelta(button, lock_threshold); return std::tuple{ret.x, ret.y}; }));
    imgui.set_function("ResetMouseDragDelta",
        sol::overload(
            []() { return ImGui::ResetMouseDragDelta(); },
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
