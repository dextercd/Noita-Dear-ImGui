#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_list_clipper(sol::table& imgui)
{
    imgui.new_usertype<ImGuiListClipper>("ListClipper",
        "Begin", sol::overload(
            [](ImGuiListClipper& clipper, int items_count) { return clipper.Begin(items_count); },
            sol::resolve<void(int, float)>(&ImGuiListClipper::Begin)),
        "End", sol::resolve<void()>(&ImGuiListClipper::End),
        "Step", sol::resolve<bool()>(&ImGuiListClipper::Step),
        "IncludeItemsByIndex", sol::resolve<void(int, int)>(&ImGuiListClipper::IncludeItemsByIndex),
        "IncludeItemByIndex", sol::resolve<void(int)>(&ImGuiListClipper::IncludeItemByIndex),
        "DisplayStart", sol::readonly(&ImGuiListClipper::DisplayStart),
        "DisplayEnd", sol::readonly(&ImGuiListClipper::DisplayEnd)
    );
}
