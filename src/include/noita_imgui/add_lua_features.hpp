#ifndef NOITA_IMGUI_ADD_LUA_FEATURES_HPP
#define NOITA_IMGUI_ADD_LUA_FEATURES_HPP

#include <noita_dear_imgui_export.h>
#include <iostream>
#include <string>

struct lua_State;

extern "C"
NOITA_DEAR_IMGUI_EXPORT void add_lua_features(lua_State* L, const std::vector<std::string>& names);

#endif // header guard
