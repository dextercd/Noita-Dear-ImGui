#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_tooltips(sol::table& imgui)
{
    imgui.set_function("BeginTooltip", sol::resolve<bool()>(ImGui::BeginTooltip));
    imgui.set_function("BeginItemTooltip", sol::resolve<bool()>(ImGui::BeginItemTooltip));
    imgui.set_function("EndTooltip", sol::resolve<void()>(ImGui::EndTooltip));
    imgui.set_function("SetTooltip",
        [](const char* text) -> void { return ImGui::SetTooltip("%s", text); });
}
