#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_color_editor(sol::table& imgui)
{
    imgui.new_enum("ColorEditFlags",
        "None",             ImGuiColorEditFlags_None,
        "NoAlpha",          ImGuiColorEditFlags_NoAlpha,
        "NoPicker",         ImGuiColorEditFlags_NoPicker,
        "NoOptions",        ImGuiColorEditFlags_NoOptions,
        "NoSmallPreview",   ImGuiColorEditFlags_NoSmallPreview,
        "NoInputs",         ImGuiColorEditFlags_NoInputs,
        "NoTooltip",        ImGuiColorEditFlags_NoTooltip,
        "NoLabel",          ImGuiColorEditFlags_NoLabel,
        "NoSidePreview",    ImGuiColorEditFlags_NoSidePreview,
        "NoDragDrop",       ImGuiColorEditFlags_NoDragDrop,
        "NoBorder",         ImGuiColorEditFlags_NoBorder,
        "AlphaBar",         ImGuiColorEditFlags_AlphaBar,
        "AlphaPreview",     ImGuiColorEditFlags_AlphaPreview,
        "AlphaPreviewHalf", ImGuiColorEditFlags_AlphaPreviewHalf,
        "HDR",              ImGuiColorEditFlags_HDR,
        "DisplayRGB",       ImGuiColorEditFlags_DisplayRGB,
        "DisplayHSV",       ImGuiColorEditFlags_DisplayHSV,
        "DisplayHex",       ImGuiColorEditFlags_DisplayHex,
        "Uint8",            ImGuiColorEditFlags_Uint8,
        "Float",            ImGuiColorEditFlags_Float,
        "PickerHueBar",     ImGuiColorEditFlags_PickerHueBar,
        "PickerHueWheel",   ImGuiColorEditFlags_PickerHueWheel,
        "InputRGB",         ImGuiColorEditFlags_InputRGB,
        "InputHSV",         ImGuiColorEditFlags_InputHSV,
        "DefaultOptions_",  ImGuiColorEditFlags_DefaultOptions_
    );

    using col3 = std::tuple<bool, float, float, float>;
    using col4 = std::tuple<bool, float, float, float, float>;

    imgui.set_function("ColorEdit3",
        sol::overload(
            [](const char* label, float r, float g, float b) -> col3 { float col[3]{r, g, b}; auto ret = ImGui::ColorEdit3(label, col); return std::tuple{ret, col[0], col[1], col[2]}; },
            [](const char* label, float r, float g, float b, ImGuiColorEditFlags flags) { float col[3]{r, g, b}; auto ret = ImGui::ColorEdit3(label, col, flags); return std::tuple{ret, col[0], col[1], col[2]}; }));

    imgui.set_function("ColorEdit4",
        sol::overload(
            [](const char* label, float r, float g, float b, float a) -> col4 { float col[4]{r, g, b, a}; auto ret = ImGui::ColorEdit4(label, col); return std::tuple{ret, col[0], col[1], col[2], col[3]}; },
            [](const char* label, float r, float g, float b, float a, ImGuiColorEditFlags flags) { float col[4]{r, g, b, a}; auto ret = ImGui::ColorEdit4(label, col, flags); return std::tuple{ret, col[0], col[1], col[2], col[3]}; }));

    imgui.set_function("ColorPicker3",
        sol::overload(
            [](const char* label, float r, float g, float b) -> col3 { float col[3]{r, g, b}; auto ret = ImGui::ColorPicker3(label, col); return std::tuple{ret, col[0], col[1], col[2]}; },
            [](const char* label, float r, float g, float b, ImGuiColorEditFlags flags) { float col[3]{r, g, b}; auto ret = ImGui::ColorPicker3(label, col, flags); return std::tuple{ret, col[0], col[1], col[2]}; }));

    imgui.set_function("ColorPicker4",
        sol::overload(
            [](const char* label, float r, float g, float b, float a) -> col4 { float col[4]{r, g, b, a}; auto ret = ImGui::ColorPicker4(label, col); return std::tuple{ret, col[0], col[1], col[2], col[3]}; },
            [](const char* label, float r, float g, float b, float a, ImGuiColorEditFlags flags) { float col[4]{r, g, b, a}; auto ret = ImGui::ColorPicker4(label, col, flags); return std::tuple{ret, col[0], col[1], col[2], col[3]}; }));

    imgui.set_function("ColorButton",
        sol::overload(
            [](const char* desc_id, float r, float g, float b, float a) -> bool { return ImGui::ColorButton(desc_id, {r, g, b, a}); },
            [](const char* desc_id, float r, float g, float b, float a, ImGuiColorEditFlags flags) { return ImGui::ColorButton(desc_id, {r, g, b, a}, flags); },
            [](const char* desc_id, float r, float g, float b, float a, ImGuiColorEditFlags flags, float size_x, float size_y) { return ImGui::ColorButton(desc_id, {r, g, b, a}, flags, {size_x, size_y}); }));
}
