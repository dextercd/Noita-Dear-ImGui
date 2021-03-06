#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_keyboard_input(sol::table& imgui)
{
    imgui.new_enum<ImGuiKey_>("Key", {
        {"None", ImGuiKey_None},
        {"Tab", ImGuiKey_Tab},
        {"LeftArrow", ImGuiKey_LeftArrow},
        {"RightArrow", ImGuiKey_RightArrow},
        {"UpArrow", ImGuiKey_UpArrow},
        {"DownArrow", ImGuiKey_DownArrow},
        {"PageUp", ImGuiKey_PageUp},
        {"PageDown", ImGuiKey_PageDown},
        {"Home", ImGuiKey_Home},
        {"End", ImGuiKey_End},
        {"Insert", ImGuiKey_Insert},
        {"Delete", ImGuiKey_Delete},
        {"Backspace", ImGuiKey_Backspace},
        {"Space", ImGuiKey_Space},
        {"Enter", ImGuiKey_Enter},
        {"Escape", ImGuiKey_Escape},
        {"LeftCtrl", ImGuiKey_LeftCtrl},
        {"LeftShift", ImGuiKey_LeftShift},
        {"LeftAlt", ImGuiKey_LeftAlt},
        {"LeftSuper", ImGuiKey_LeftSuper},
        {"RightCtrl", ImGuiKey_RightCtrl},
        {"RightShift", ImGuiKey_RightShift},
        {"RightAlt", ImGuiKey_RightAlt},
        {"RightSuper", ImGuiKey_RightSuper},
        {"Menu", ImGuiKey_Menu},
        {"_0", ImGuiKey_0},
        {"_1", ImGuiKey_1},
        {"_2", ImGuiKey_2},
        {"_3", ImGuiKey_3},
        {"_4", ImGuiKey_4},
        {"_5", ImGuiKey_5},
        {"_6", ImGuiKey_6},
        {"_7", ImGuiKey_7},
        {"_8", ImGuiKey_8},
        {"_9", ImGuiKey_9},
        {"A", ImGuiKey_A},
        {"B", ImGuiKey_B},
        {"C", ImGuiKey_C},
        {"D", ImGuiKey_D},
        {"E", ImGuiKey_E},
        {"F", ImGuiKey_F},
        {"G", ImGuiKey_G},
        {"H", ImGuiKey_H},
        {"I", ImGuiKey_I},
        {"J", ImGuiKey_J},
        {"K", ImGuiKey_K},
        {"L", ImGuiKey_L},
        {"M", ImGuiKey_M},
        {"N", ImGuiKey_N},
        {"O", ImGuiKey_O},
        {"P", ImGuiKey_P},
        {"Q", ImGuiKey_Q},
        {"R", ImGuiKey_R},
        {"S", ImGuiKey_S},
        {"T", ImGuiKey_T},
        {"U", ImGuiKey_U},
        {"V", ImGuiKey_V},
        {"W", ImGuiKey_W},
        {"X", ImGuiKey_X},
        {"Y", ImGuiKey_Y},
        {"Z", ImGuiKey_Z},
        {"F1", ImGuiKey_F1},
        {"F2", ImGuiKey_F2},
        {"F3", ImGuiKey_F3},
        {"F4", ImGuiKey_F4},
        {"F5", ImGuiKey_F5},
        {"F6", ImGuiKey_F6},
        {"F7", ImGuiKey_F7},
        {"F8", ImGuiKey_F8},
        {"F9", ImGuiKey_F9},
        {"F10", ImGuiKey_F10},
        {"F11", ImGuiKey_F11},
        {"F12", ImGuiKey_F12},
        {"Apostrophe", ImGuiKey_Apostrophe},
        {"Comma", ImGuiKey_Comma},
        {"Minus", ImGuiKey_Minus},
        {"Period", ImGuiKey_Period},
        {"Slash", ImGuiKey_Slash},
        {"Semicolon", ImGuiKey_Semicolon},
        {"Equal", ImGuiKey_Equal},
        {"LeftBracket", ImGuiKey_LeftBracket},
        {"Backslash", ImGuiKey_Backslash},
        {"RightBracket", ImGuiKey_RightBracket},
        {"GraveAccent", ImGuiKey_GraveAccent},
        {"CapsLock", ImGuiKey_CapsLock},
        {"ScrollLock", ImGuiKey_ScrollLock},
        {"NumLock", ImGuiKey_NumLock},
        {"PrintScreen", ImGuiKey_PrintScreen},
        {"Pause", ImGuiKey_Pause},
        {"Keypad0", ImGuiKey_Keypad0},
        {"Keypad1", ImGuiKey_Keypad1},
        {"Keypad2", ImGuiKey_Keypad2},
        {"Keypad3", ImGuiKey_Keypad3},
        {"Keypad4", ImGuiKey_Keypad4},
        {"Keypad5", ImGuiKey_Keypad5},
        {"Keypad6", ImGuiKey_Keypad6},
        {"Keypad7", ImGuiKey_Keypad7},
        {"Keypad8", ImGuiKey_Keypad8},
        {"Keypad9", ImGuiKey_Keypad9},
        {"KeypadDecimal", ImGuiKey_KeypadDecimal},
        {"KeypadDivide", ImGuiKey_KeypadDivide},
        {"KeypadMultiply", ImGuiKey_KeypadMultiply},
        {"KeypadSubtract", ImGuiKey_KeypadSubtract},
        {"KeypadAdd", ImGuiKey_KeypadAdd},
        {"KeypadEnter", ImGuiKey_KeypadEnter},
        {"KeypadEqual", ImGuiKey_KeypadEqual},
        {"GamepadStart", ImGuiKey_GamepadStart},
        {"GamepadBack", ImGuiKey_GamepadBack},
        {"GamepadFaceUp", ImGuiKey_GamepadFaceUp},
        {"GamepadFaceDown", ImGuiKey_GamepadFaceDown},
        {"GamepadFaceLeft", ImGuiKey_GamepadFaceLeft},
        {"GamepadFaceRight", ImGuiKey_GamepadFaceRight},
        {"GamepadDpadUp", ImGuiKey_GamepadDpadUp},
        {"GamepadDpadDown", ImGuiKey_GamepadDpadDown},
        {"GamepadDpadLeft", ImGuiKey_GamepadDpadLeft},
        {"GamepadDpadRight", ImGuiKey_GamepadDpadRight},
        {"GamepadL1", ImGuiKey_GamepadL1},
        {"GamepadR1", ImGuiKey_GamepadR1},
        {"GamepadL2", ImGuiKey_GamepadL2},
        {"GamepadR2", ImGuiKey_GamepadR2},
        {"GamepadL3", ImGuiKey_GamepadL3},
        {"GamepadR3", ImGuiKey_GamepadR3},
        {"GamepadLStickUp", ImGuiKey_GamepadLStickUp},
        {"GamepadLStickDown", ImGuiKey_GamepadLStickDown},
        {"GamepadLStickLeft", ImGuiKey_GamepadLStickLeft},
        {"GamepadLStickRight", ImGuiKey_GamepadLStickRight},
        {"GamepadRStickUp", ImGuiKey_GamepadRStickUp},
        {"GamepadRStickDown", ImGuiKey_GamepadRStickDown},
        {"GamepadRStickLeft", ImGuiKey_GamepadRStickLeft},
        {"GamepadRStickRight", ImGuiKey_GamepadRStickRight},
        {"ModCtrl", ImGuiKey_ModCtrl},
        {"ModShift", ImGuiKey_ModShift},
        {"ModAlt", ImGuiKey_ModAlt},
        {"ModSuper", ImGuiKey_ModSuper},
        {"COUNT", ImGuiKey_COUNT},
    });

    imgui.set_function("IsKeyDown", sol::resolve<bool(ImGuiKey)>(ImGui::IsKeyDown));
    imgui.set_function("IsKeyPressed",
        sol::overload(
            [](ImGuiKey key) { return ImGui::IsKeyPressed(key); },
            sol::resolve<bool(ImGuiKey, bool)>(ImGui::IsKeyPressed)));
    imgui.set_function("IsKeyReleased", sol::resolve<bool(ImGuiKey)>(ImGui::IsKeyReleased));
    imgui.set_function("GetKeyPressedAmount", sol::resolve<int(ImGuiKey, float, float)>(ImGui::GetKeyPressedAmount));
    imgui.set_function("GetKeyName", sol::resolve<const char*(ImGuiKey)>(ImGui::GetKeyName));
    imgui.set_function("SetNextFrameWantCaptureKeyboard", sol::resolve<void(bool)>(ImGui::SetNextFrameWantCaptureKeyboard));
}
