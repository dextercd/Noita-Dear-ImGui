#include <iostream>
#include <string>

#include <sol/sol.hpp>

#include "version_number.hpp"

void add_imgui_gui_io(sol::table&);
void add_imgui_windows(sol::table&);
void add_imgui_text(sol::table&);
void add_imgui_menu(sol::table&);
void add_imgui_widgets_main(sol::table&);

sol::table load_imgui(sol::this_state s, sol::table load_params)
{
    std::string version = load_params["version"];
    std::cerr << "Version: " << version << "\n";
    sol::state_view lua{s};
    sol::table imgui = lua.create_table();
    add_imgui_gui_io(imgui);
    add_imgui_windows(imgui);
    add_imgui_text(imgui);
    add_imgui_menu(imgui);
    add_imgui_widgets_main(imgui);

    return imgui;
}

void add_lua_features(lua_State* L)
{
    sol::state_view lua{L};
    lua.set_function("load_imgui", load_imgui);
}
