#include <sol/sol.hpp>
#include <iostream>

void add_lua_features(lua_State* L)
{
    sol::state_view lua{L};

    auto imgui = lua["imgui"].get_or_create<sol::table>();
    imgui.set_function("log", []() { std::cout << "WHOOO!\n" << std::flush; });
}
