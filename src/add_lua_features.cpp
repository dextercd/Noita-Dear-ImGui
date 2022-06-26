#include <iostream>
#include <string>

#include <sol/sol.hpp>

#include <noita_dear_imgui_export.h>
#include <noita_imgui/version_number.hpp>

void add_imgui_clipboard(sol::table&);
void add_imgui_color_editor(sol::table&);
void add_imgui_combo_box(sol::table&);
void add_imgui_common(sol::table&);
void add_imgui_drag_sliders(sol::table&);
void add_imgui_font(sol::table&);
void add_imgui_gui_io(sol::table&);
void add_imgui_keyboard_input(sol::table&);
void add_imgui_layout(sol::table&);
void add_imgui_menu(sol::table&);
void add_imgui_mouse_input(sol::table&);
void add_imgui_param_stacks(sol::table&);
void add_imgui_regular_sliders(sol::table&);
void add_imgui_scopes(sol::table&);
void add_imgui_tables(sol::table&);
void add_imgui_text(sol::table&);
void add_imgui_text_input(sol::table&);
void add_imgui_tooltips(sol::table&);
void add_imgui_trees(sol::table&);
void add_imgui_widget_utils(sol::table&);
void add_imgui_widgets_main(sol::table&);
void add_imgui_windows(sol::table&);

sol::table load_imgui(sol::this_state s, sol::table load_params)
{
    std::string version = load_params["version"];
    sol::state_view lua{s};
    sol::table imgui = lua.create_table();

    add_imgui_clipboard(imgui);
    add_imgui_color_editor(imgui);
    add_imgui_combo_box(imgui);
    add_imgui_common(imgui);
    add_imgui_drag_sliders(imgui);
    add_imgui_font(imgui);
    add_imgui_gui_io(imgui);
    add_imgui_keyboard_input(imgui);
    add_imgui_layout(imgui);
    add_imgui_menu(imgui);
    add_imgui_mouse_input(imgui);
    add_imgui_param_stacks(imgui);
    add_imgui_regular_sliders(imgui);
    add_imgui_scopes(imgui);
    add_imgui_tables(imgui);
    add_imgui_text(imgui);
    add_imgui_text_input(imgui);
    add_imgui_tooltips(imgui);
    add_imgui_trees(imgui);
    add_imgui_widget_utils(imgui);
    add_imgui_widgets_main(imgui);
    add_imgui_windows(imgui);

    return imgui;
}

extern "C"
NOITA_DEAR_IMGUI_EXPORT void add_lua_features(lua_State* L)
{
    sol::state_view lua{L};
    lua.set_function("load_imgui", load_imgui);
}
