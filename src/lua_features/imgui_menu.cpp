#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_menu(sol::table& imgui)
{
    imgui.set_function("BeginMenuBar", &ImGui::BeginMenuBar);
    imgui.set_function("EndMenuBar", &ImGui::EndMenuBar);
    imgui.set_function("BeginMainMenuBar", &ImGui::BeginMainMenuBar);
    imgui.set_function("EndMainMenuBar", &ImGui::EndMainMenuBar);
    imgui.set_function("BeginMenu",
        sol::overload(
            [](const char* label) { return ImGui::BeginMenu(label); },
            &ImGui::BeginMenu));
    imgui.set_function("EndMenu", &ImGui::EndMenu);
    imgui.set_function("MenuItem",
        sol::overload(
            [](const char* label) { return ImGui::MenuItem(label); },
            [](const char* label, const char* shortcut) { return ImGui::MenuItem(label, shortcut); },
            [](const char* label, const char* shortcut, bool selected) { auto ret = ImGui::MenuItem(label, shortcut); return std::tuple{ret, selected}; },
            [](const char* label, const char* shortcut, bool selected, bool enabled) { auto ret = ImGui::MenuItem(label, shortcut, enabled); return std::tuple{ret, selected}; }
        ));
}
