#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_widgets_main(sol::table& imgui)
{
    imgui.new_enum("ButtonFlags",
        "None",              ImGuiButtonFlags_None,
        "MouseButtonLeft",   ImGuiButtonFlags_MouseButtonLeft,
        "MouseButtonRight",  ImGuiButtonFlags_MouseButtonRight,
        "MouseButtonMiddle", ImGuiButtonFlags_MouseButtonMiddle
    );

    imgui.set_function("Button",
        sol::overload(
            [](const char* label) { return ImGui::Button(label); },
            [](const char* label, float width, float height) { return ImGui::Button(label, {width, height}); }));
    imgui.set_function("SmallButton", &ImGui::SmallButton);
    imgui.set_function("InvisibleButton",
        sol::overload(
            [](const char* str_id, float size_x, float size_y) { return ImGui::InvisibleButton(str_id, {size_x, size_y}); },
            [](const char* str_id, float size_x, float size_y, ImGuiButtonFlags flags) { return ImGui::InvisibleButton(str_id, {size_x, size_y}, flags); }));
    imgui.set_function("ArrowButton", &ImGui::ArrowButton);
    imgui.set_function("Checkbox", [](const char* label, bool value) { bool changed = ImGui::Checkbox(label, &value); return std::tuple{changed, value}; });
    imgui.set_function("CheckboxFlags",
        [](const char* label, unsigned flags, unsigned flags_value) { auto ret = ImGui::CheckboxFlags(label, &flags, flags_value); return std::tuple{ret, flags}; });
    imgui.set_function("RadioButton", sol::resolve<bool(const char*, bool)>(ImGui::RadioButton));
    imgui.set_function("ProgressBar",
        sol::overload(
            [](float fraction) { return ImGui::ProgressBar(fraction); },
            [](float fraction, float size_x) { return ImGui::ProgressBar(fraction, {size_x, 0}); },
            [](float fraction, float size_x, float size_y) { return ImGui::ProgressBar(fraction, {size_x, size_y}); },
            [](float fraction, float size_x, float size_y, const char* overlay) { return ImGui::ProgressBar(fraction, {size_x, size_y}, overlay); }));
    imgui.set_function("Bullet", &ImGui::Bullet);
}
