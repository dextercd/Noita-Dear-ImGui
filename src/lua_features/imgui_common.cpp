#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_common(sol::table& imgui)
{
    imgui.new_enum("Cond",
        "None",         ImGuiCond_None,
        "Always",       ImGuiCond_Always,
        "Once",         ImGuiCond_Once,
        "FirstUseEver", ImGuiCond_FirstUseEver,
        "Appearing",    ImGuiCond_Appearing
    );
}
