#include <iostream>

#include <sol/sol.hpp>

void add_imgui_gui_io(sol::table&);
void add_imgui_windows(sol::table&);
void add_imgui_text(sol::table&);

void add_lua_features(lua_State* L)
{
    sol::state_view lua{L};

    auto imgui = lua["imgui"].get_or_create<sol::table>();
    add_imgui_gui_io(imgui);
    add_imgui_windows(imgui);
    add_imgui_text(imgui);
}
