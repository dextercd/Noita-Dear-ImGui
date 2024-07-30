#include <cassert>
#include <cstdint>

#include <imgui.h>

#include "style.hpp"

constexpr std::uint8_t hex_to_int(char left, char right)
{
    assert(left >= '0' && left <= '9' || left >= 'a' && left <= 'f');
    assert(right >= '0' && right <= '9' || right >= 'a' && right <= 'f');

    auto left_value = left >= '0' && left <= '9' ? left - '0' : left - 'a' + 10;
    auto right_value = right >= '0' && right <= '9' ? right - '0' : right - 'a' + 10;

    return left_value * 16 + right_value;
}

static_assert(hex_to_int('0', 'f') == 15);
static_assert(hex_to_int('f', '0') == 240);
static_assert(hex_to_int('1', 'f') == 31);
static_assert(hex_to_int('f', '1') == 241);

constexpr ImVec4 color(const char (&spec)[8])
{
    std::uint8_t r = hex_to_int(spec[1], spec[2]);
    std::uint8_t g = hex_to_int(spec[3], spec[4]);
    std::uint8_t b = hex_to_int(spec[5], spec[6]);

    return ImVec4(
        r / 255.0f,
        g / 255.0f,
        b / 255.0f,
        1.0f
    );
}

constexpr ImVec4 color(const char (&spec)[10])
{
    std::uint8_t r = hex_to_int(spec[1], spec[2]);
    std::uint8_t g = hex_to_int(spec[3], spec[4]);
    std::uint8_t b = hex_to_int(spec[5], spec[6]);
    std::uint8_t a = hex_to_int(spec[7], spec[8]);

    return ImVec4(
        r / 255.0f,
        g / 255.0f,
        b / 255.0f,
        a / 255.0f
    );
}

constexpr auto full_white = color("#ffffff");

constexpr auto background_dark = color("#1a140f");
constexpr auto background_frame = color("#4d45458a");
constexpr auto background_frame_active = color("#b39f828a");

constexpr auto accent_main = color("#947f64");
constexpr auto accent_light = color("#b39f82");

constexpr auto accent_light_white = color("#b6b6b6");
constexpr auto accent_white = color("#a4a09d");
constexpr auto accent_grey = color("#8a8886");

void noita_imgui_style(ImGuiStyle* dst)
{
    if (!dst)
        dst = &ImGui::GetStyle();

    ImGui::StyleColorsDark(dst);
    dst->Colors[ImGuiCol_TitleBgActive] = accent_main;
    dst->Colors[ImGuiCol_TitleBg] = accent_light;
    dst->Colors[ImGuiCol_Border] = accent_main;

    dst->Colors[ImGuiCol_WindowBg] = color("#0e0d0cf1");

    dst->Colors[ImGuiCol_FrameBg] = background_frame;
    dst->Colors[ImGuiCol_FrameBgHovered] = background_frame_active;
    dst->Colors[ImGuiCol_FrameBgActive] = background_frame_active;

    dst->Colors[ImGuiCol_CheckMark] = full_white;

    dst->Colors[ImGuiCol_SliderGrab] = color("#989187");
    dst->Colors[ImGuiCol_SliderGrabActive] = color("#c5bbad");

    dst->Colors[ImGuiCol_Button] = color("#ffd07f66");
    dst->Colors[ImGuiCol_ButtonHovered] = accent_light;
    dst->Colors[ImGuiCol_ButtonActive] = accent_main;

    dst->Colors[ImGuiCol_Header] = color("#ffc48c4f");
    dst->Colors[ImGuiCol_HeaderHovered] = color("#7d858fcc");
    dst->Colors[ImGuiCol_HeaderActive] = color("#a1a3a6");

    dst->Colors[ImGuiCol_Separator] = color("#b5a86980");
    dst->Colors[ImGuiCol_SeparatorHovered] = color("#d6cfa880");
    dst->Colors[ImGuiCol_SeparatorActive] = color("#fafafa");

    dst->Colors[ImGuiCol_ResizeGrip] = color("#ffffff33");
    dst->Colors[ImGuiCol_ResizeGripHovered] = color("#c4bd8cab");
    dst->Colors[ImGuiCol_ResizeGripActive] = color("#f7de82f2");

    dst->Colors[ImGuiCol_Tab] = color("#40352b7c");
    dst->Colors[ImGuiCol_TabHovered] = color("#a990787d");
    dst->Colors[ImGuiCol_TabSelected] = color("#4d4545ff");
    dst->Colors[ImGuiCol_TabDimmed] = dst->Colors[ImGuiCol_Tab];
    dst->Colors[ImGuiCol_TabDimmedSelected] = dst->Colors[ImGuiCol_TabSelected];
    dst->Colors[ImGuiCol_TabSelectedOverline] = color("#eacf1cff");
    dst->Colors[ImGuiCol_TabDimmedSelectedOverline] = color("#f5e46fff");

    dst->Colors[ImGuiCol_TextSelectedBg] = color("#2e8cffa3");

    dst->Colors[ImGuiCol_NavHighlight] = background_frame_active;

}
