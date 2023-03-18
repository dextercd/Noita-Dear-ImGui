#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_scopes(sol::table& imgui)
{
    imgui.set_function("PushID",
        sol::overload(
            sol::resolve<void(const char*)>(ImGui::PushID),
            sol::resolve<void(int)>(ImGui::PushID)));

    imgui.set_function("PopID", sol::resolve<void()>(ImGui::PopID));
    imgui.set_function("GetID", sol::resolve<unsigned int(const char*)>(ImGui::GetID));
}
