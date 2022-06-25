#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_scopes(sol::table& imgui)
{
    imgui.set_function("PushID",
        sol::overload(
            [](const char* str_id) { return ImGui::PushID(str_id); },
            [](int int_id) { return ImGui::PushID(int_id); }));

    imgui.set_function("PopID", sol::resolve<void()>(ImGui::PopID));
    imgui.set_function("GetID", sol::resolve<unsigned int(const char*)>(ImGui::GetID));
}
