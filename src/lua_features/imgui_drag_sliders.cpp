#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_drag_sliders(sol::table& imgui)
{
    imgui.new_enum("SliderFlags",
        "None",            ImGuiSliderFlags_None,
        "AlwaysClamp",     ImGuiSliderFlags_AlwaysClamp,
        "Logarithmic",     ImGuiSliderFlags_Logarithmic,
        "NoRoundToFormat", ImGuiSliderFlags_NoRoundToFormat,
        "NoInput",         ImGuiSliderFlags_NoInput,
        "InvalidMask_",    ImGuiSliderFlags_InvalidMask_
    );

    imgui.set_function("DragFloat",
        sol::overload(
            [](const char* label, float v) { auto ret = ImGui::DragFloat(label, &v); return std::tuple{ret, v}; },
            [](const char* label, float v, float v_speed) { auto ret = ImGui::DragFloat(label, &v, v_speed); return std::tuple{ret, v}; },
            [](const char* label, float v, float v_speed, float v_min) { auto ret = ImGui::DragFloat(label, &v, v_speed, v_min); return std::tuple{ret, v}; },
            [](const char* label, float v, float v_speed, float v_min, float v_max) { auto ret = ImGui::DragFloat(label, &v, v_speed, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v, float v_speed, float v_min, float v_max, const char* format) { auto ret = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { auto ret = ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("DragFloat2",
        sol::overload(
            [](const char* label, float v1, float v2) { float v[2]{v1, v2}; auto ret = ImGui::DragFloat2(label, v); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v_speed) { float v[2]{v1, v2}; auto ret = ImGui::DragFloat2(label, v, v_speed); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v_speed, float v_min) { float v[2]{v1, v2}; auto ret = ImGui::DragFloat2(label, v, v_speed, v_min); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v_speed, float v_min, float v_max) { float v[2]{v1, v2}; auto ret = ImGui::DragFloat2(label, v, v_speed, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v_speed, float v_min, float v_max, const char* format) { float v[2]{v1, v2}; auto ret = ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { float v[2]{v1, v2}; auto ret = ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("DragFloat3",
        sol::overload(
            [](const char* label, float v1, float v2, float v3) { float v[3]{v1, v2, v3}; auto ret = ImGui::DragFloat3(label, v); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v_speed) { float v[3]{v1, v2, v3}; auto ret = ImGui::DragFloat3(label, v, v_speed); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v_speed, float v_min) { float v[3]{v1, v2, v3}; auto ret = ImGui::DragFloat3(label, v, v_speed, v_min); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v_speed, float v_min, float v_max) { float v[3]{v1, v2, v3}; auto ret = ImGui::DragFloat3(label, v, v_speed, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v_speed, float v_min, float v_max, const char* format) { float v[3]{v1, v2, v3}; auto ret = ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { float v[3]{v1, v2, v3}; auto ret = ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("DragFloat4",
        sol::overload(
            [](const char* label, float v1, float v2, float v3, float v4) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragFloat4(label, v); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v4, float v_speed) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragFloat4(label, v, v_speed); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v4, float v_speed, float v_min) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragFloat4(label, v, v_speed, v_min); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v4, float v_speed, float v_min, float v_max) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragFloat4(label, v, v_speed, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v4, float v_speed, float v_min, float v_max, const char* format) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v4, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("DragFloatRange2",
        sol::overload(
            [](const char* label, float v_current_min, float v_current_max) { auto ret = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, float v_current_min, float v_current_max, float v_speed) { auto ret = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, float v_current_min, float v_current_max, float v_speed, float v_min) { auto ret = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max) { auto ret = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max, const char* format) { auto ret = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max, const char* format, const char* format_max) { auto ret = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, float v_current_min, float v_current_max, float v_speed, float v_min, float v_max, const char* format, const char* format_max, ImGuiSliderFlags flags) { auto ret = ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, flags); return std::tuple{ret, v_current_min, v_current_max}; }));

    imgui.set_function("DragInt",
        sol::overload(
            [](const char* label, int v) { auto ret = ImGui::DragInt(label, &v); return std::tuple{ret, v}; },
            [](const char* label, int v, float v_speed) { auto ret = ImGui::DragInt(label, &v, v_speed); return std::tuple{ret, v}; },
            [](const char* label, int v, float v_speed, int v_min) { auto ret = ImGui::DragInt(label, &v, v_speed, v_min); return std::tuple{ret, v}; },
            [](const char* label, int v, float v_speed, int v_min, int v_max) { auto ret = ImGui::DragInt(label, &v, v_speed, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, int v, float v_speed, int v_min, int v_max, const char* format) { auto ret = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, int v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { auto ret = ImGui::DragInt(label, &v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("DragInt2",
        sol::overload(
            [](const char* label, int v1, int v2) { int v[2]{v1, v2}; auto ret = ImGui::DragInt2(label, v); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, float v_speed) { int v[2]{v1, v2}; auto ret = ImGui::DragInt2(label, v, v_speed); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, float v_speed, int v_min) { int v[2]{v1, v2}; auto ret = ImGui::DragInt2(label, v, v_speed, v_min); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, float v_speed, int v_min, int v_max) { int v[2]{v1, v2}; auto ret = ImGui::DragInt2(label, v, v_speed, v_min, v_max); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, float v_speed, int v_min, int v_max, const char* format) { int v[2]{v1, v2}; auto ret = ImGui::DragInt2(label, v, v_speed, v_min, v_max, format); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { int v[2]{v1, v2}; auto ret = ImGui::DragInt2(label, v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v[0], v[1]}; }));

    imgui.set_function("DragInt3",
        sol::overload(
            [](const char* label, int v1, int v2, int v3) { int v[3]{v1, v2, v3}; auto ret = ImGui::DragInt3(label, v); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, float v_speed) { int v[3]{v1, v2, v3}; auto ret = ImGui::DragInt3(label, v, v_speed); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, float v_speed, int v_min) { int v[3]{v1, v2, v3}; auto ret = ImGui::DragInt3(label, v, v_speed, v_min); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, float v_speed, int v_min, int v_max) { int v[3]{v1, v2, v3}; auto ret = ImGui::DragInt3(label, v, v_speed, v_min, v_max); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, float v_speed, int v_min, int v_max, const char* format) { int v[3]{v1, v2, v3}; auto ret = ImGui::DragInt3(label, v, v_speed, v_min, v_max, format); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { int v[3]{v1, v2, v3}; auto ret = ImGui::DragInt3(label, v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v[0], v[1], v[2]}; }));

    imgui.set_function("DragInt4",
        sol::overload(
            [](const char* label, int v1, int v2, int v3, int v4) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragInt4(label, v); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, float v_speed) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragInt4(label, v, v_speed); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, float v_speed, int v_min) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragInt4(label, v, v_speed, v_min); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, float v_speed, int v_min, int v_max) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragInt4(label, v, v_speed, v_min, v_max); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, float v_speed, int v_min, int v_max, const char* format) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragInt4(label, v, v_speed, v_min, v_max, format); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::DragInt4(label, v, v_speed, v_min, v_max, format, flags); return std::tuple{ret, v[0], v[1], v[2], v[3]}; }));

    imgui.set_function("DragIntRange2",
        sol::overload(
            [](const char* label, int v_current_min, int v_current_max) { auto ret = ImGui::DragIntRange2(label, &v_current_min, &v_current_max); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, int v_current_min, int v_current_max, float v_speed) { auto ret = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, int v_current_min, int v_current_max, float v_speed, int v_min) { auto ret = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max) { auto ret = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max, const char* format) { auto ret = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max, const char* format, const char* format_max) { auto ret = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max); return std::tuple{ret, v_current_min, v_current_max}; },
            [](const char* label, int v_current_min, int v_current_max, float v_speed, int v_min, int v_max, const char* format, const char* format_max, ImGuiSliderFlags flags) { auto ret = ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, flags); return std::tuple{ret, v_current_min, v_current_max}; }));
}
