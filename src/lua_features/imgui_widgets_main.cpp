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
            &ImGui::Button));
    imgui.set_function("SmallButton", &ImGui::SmallButton);
    imgui.set_function("InvisibleButton",
        sol::overload(
            [](const char* str_id, float size_x, float size_y) { return ImGui::InvisibleButton(str_id, {size_x, size_y}); },
            [](const char* str_id, float size_x, float size_y, ImGuiButtonFlags flags) { return ImGui::InvisibleButton(str_id, {size_x, size_y}, flags); }));
    imgui.set_function("ArrowButton", &ImGui::ArrowButton);
    imgui.set_function("Image",
        sol::overload(
            [](ImTextureID texid, float size_x, float size_y) { return ImGui::Image(texid, {size_x, size_y}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y) { return ImGui::Image(texid, {size_x, size_y}, {uv0_x, uv0_y}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y, float uv1_x, float uv1_y) { return ImGui::Image(texid, {size_x, size_y}, {uv0_x, uv0_y}, {uv1_x, uv1_y}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y, float uv1_x, float uv1_y, float tint_r, float tint_g, float tint_b, float tint_a) { return ImGui::Image(texid, {size_x, size_y}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, {tint_r, tint_g, tint_b, tint_a}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y, float uv1_x, float uv1_y, float tint_r, float tint_g, float tint_b, float tint_a, float border_r, float border_g, float border_b, float border_a) { return ImGui::Image(texid, {size_x, size_y}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, {tint_r, tint_g, tint_b, tint_a}, {border_r, border_g, border_b, border_a}); }));
    imgui.set_function("ImageButton",
        sol::overload(
            [](ImTextureID texid, float size_x, float size_y) { return ImGui::ImageButton(texid, {size_x, size_y}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y) { return ImGui::ImageButton(texid, {size_x, size_y}, {uv0_x, uv0_y}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y, float uv1_x, float uv1_y) { return ImGui::ImageButton(texid, {size_x, size_y}, {uv0_x, uv0_y}, {uv1_x, uv1_y}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y, float uv1_x, float uv1_y, int frame_padding) { return ImGui::ImageButton(texid, {size_x, size_y}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, frame_padding); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y, float uv1_x, float uv1_y, int frame_padding, float bg_r, float bg_g, float bg_b, float bg_a) { return ImGui::ImageButton(texid, {size_x, size_y}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, frame_padding, {bg_r, bg_g, bg_b, bg_a}); },
            [](ImTextureID texid, float size_x, float size_y, float uv0_x, float uv0_y, float uv1_x, float uv1_y, int frame_padding, float bg_r, float bg_g, float bg_b, float bg_a, float border_r, float border_g, float border_b, float border_a) { return ImGui::ImageButton(texid, {size_x, size_y}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, frame_padding, {bg_r, bg_g, bg_b, bg_a}, {border_r, border_g, border_b, border_a}); }));
    imgui.set_function("Checkbox", &ImGui::Checkbox);
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
