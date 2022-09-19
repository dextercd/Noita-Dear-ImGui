#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_disable(sol::table& imgui)
{
    imgui.set_function("BeginDisabled",
        sol::overload(
            []() { return ImGui::BeginDisabled(); },
            sol::resolve<void(bool)>(ImGui::BeginDisabled)));

    imgui.set_function("EndDisabled", sol::resolve<void()>(ImGui::EndDisabled));
}
