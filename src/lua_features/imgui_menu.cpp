#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_menu(sol::table& imgui)
{
    imgui.set_function("BeginMenuBar", sol::resolve<bool()>(ImGui::BeginMenuBar));
    imgui.set_function("EndMenuBar", sol::resolve<void()>(ImGui::EndMenuBar));
    imgui.set_function("BeginMainMenuBar", sol::resolve<bool()>(ImGui::BeginMainMenuBar));
    imgui.set_function("EndMainMenuBar", sol::resolve<void()>(ImGui::EndMainMenuBar));
    imgui.set_function("BeginMenu",
        sol::overload(
            [](const char* label) { return ImGui::BeginMenu(label); },
            &ImGui::BeginMenu));
    imgui.set_function("EndMenu", sol::resolve<void()>(ImGui::EndMenu));
    imgui.set_function("MenuItem",
        sol::overload(
            [](const char* label) { return ImGui::MenuItem(label); },
            [](const char* label, const char* shortcut) { return ImGui::MenuItem(label, shortcut); },
            [](const char* label, const char* shortcut, bool selected) { auto ret = ImGui::MenuItem(label, shortcut, &selected); return std::tuple{ret, selected}; },
            [](const char* label, const char* shortcut, bool selected, bool enabled) { auto ret = ImGui::MenuItem(label, shortcut, &selected, enabled); return std::tuple{ret, selected}; }
        ));
}
