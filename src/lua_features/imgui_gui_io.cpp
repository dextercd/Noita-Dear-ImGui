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

    imgui.set_function("GetIO", sol::resolve<ImGuiIO&()>(ImGui::GetIO));
}
