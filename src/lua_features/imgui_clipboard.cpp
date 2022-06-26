#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_clipboard(sol::table& imgui)
{
    imgui.set_function("GetClipboardText", sol::resolve<const char*()>(ImGui::GetClipboardText));
    imgui.set_function("SetClipboardText", sol::resolve<void(const char*)>(ImGui::SetClipboardText));
}
