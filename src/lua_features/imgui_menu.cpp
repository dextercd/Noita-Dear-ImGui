#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_menu(sol::table& imgui)
{
/*
    IMGUI_API bool          BeginMenu(const char* label, bool enabled = true);                  // create a sub-menu entry. only call EndMenu() if this returns true!
    IMGUI_API bool          MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);  // return true when activated.
    IMGUI_API bool          MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);              // return true when activated + toggle (*p_selected) if p_selected != NULL
*/

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
