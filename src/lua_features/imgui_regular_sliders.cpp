#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_regular_sliders(sol::table& imgui)
{
    // imgui.new_enum("SliderFlags", ... registered  in add_imgui_drag_sliders

    imgui.set_function("SliderFloat",
        sol::overload(
            [](const char* label, float v, float v_min, float v_max) { auto ret = ImGui::SliderFloat(label, &v, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v, float v_min, float v_max, const char* format) { auto ret = ImGui::SliderFloat(label, &v, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { auto ret = ImGui::SliderFloat(label, &v, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("SliderFloat2",
        sol::overload(
            [](const char* label, float v1, float v2, float v_min, float v_max) { float v[2]{v1, v2}; auto ret = ImGui::SliderFloat2(label, v, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v_min, float v_max, const char* format) { float v[2]{v1, v2}; auto ret = ImGui::SliderFloat2(label, v, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { float v[2]{v1, v2}; auto ret = ImGui::SliderFloat2(label, v, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("SliderFloat3",
        sol::overload(
            [](const char* label, float v1, float v2, float v3, float v_min, float v_max) { float v[3]{v1, v2, v3}; auto ret = ImGui::SliderFloat3(label, v, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v_min, float v_max, const char* format) { float v[3]{v1, v2, v3}; auto ret = ImGui::SliderFloat3(label, v, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { float v[3]{v1, v2, v3}; auto ret = ImGui::SliderFloat3(label, v, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("SliderFloat4",
        sol::overload(
            [](const char* label, float v1, float v2, float v3, float v4, float v_min, float v_max) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::SliderFloat4(label, v, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v4, float v_min, float v_max, const char* format) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::SliderFloat4(label, v, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, float v1, float v2, float v3, float v4, float v_min, float v_max, const char* format, ImGuiSliderFlags flags) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::SliderFloat4(label, v, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("SliderInt",
        sol::overload(
            [](const char* label, int v, int v_min, int v_max) { auto ret = ImGui::SliderInt(label, &v, v_min, v_max); return std::tuple{ret, v}; },
            [](const char* label, int v, int v_min, int v_max, const char* format) { auto ret = ImGui::SliderInt(label, &v, v_min, v_max, format); return std::tuple{ret, v}; },
            [](const char* label, int v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { auto ret = ImGui::SliderInt(label, &v, v_min, v_max, format, flags); return std::tuple{ret, v}; }));

    imgui.set_function("SliderInt2",
        sol::overload(
            [](const char* label, int v1, int v2, int v_min, int v_max) { int v[2]{v1, v2}; auto ret = ImGui::SliderInt2(label, v, v_min, v_max); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, int v_min, int v_max, const char* format) { int v[2]{v1, v2}; auto ret = ImGui::SliderInt2(label, v, v_min, v_max, format); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { int v[2]{v1, v2}; auto ret = ImGui::SliderInt2(label, v, v_min, v_max, format, flags); return std::tuple{ret, v[0], v[1]}; }));

    imgui.set_function("SliderInt3",
        sol::overload(
            [](const char* label, int v1, int v2, int v3, int v_min, int v_max) { int v[3]{v1, v2, v3}; auto ret = ImGui::SliderInt3(label, v, v_min, v_max); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, int v_min, int v_max, const char* format) { int v[3]{v1, v2, v3}; auto ret = ImGui::SliderInt3(label, v, v_min, v_max, format); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { int v[3]{v1, v2, v3}; auto ret = ImGui::SliderInt3(label, v, v_min, v_max, format, flags); return std::tuple{ret, v[0], v[1], v[2]}; }));

    imgui.set_function("SliderInt4",
        sol::overload(
            [](const char* label, int v1, int v2, int v3, int v4, int v_min, int v_max) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::SliderInt4(label, v, v_min, v_max); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, int v_min, int v_max, const char* format) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::SliderInt4(label, v, v_min, v_max, format); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, int v_min, int v_max, const char* format, ImGuiSliderFlags flags) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::SliderInt4(label, v, v_min, v_max, format, flags); return std::tuple{ret, v[0], v[1], v[2], v[3]}; }));
}
