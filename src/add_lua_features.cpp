#include <iostream>
#include <string>
#include <vector>

#include <sol/sol.hpp>

#include <noita_dear_imgui_export.h>
#include <noita_imgui/version_info.hpp>
#include <noita_imgui/version_number.hpp>
#include "version_compat_window.hpp"

void add_container(sol::table&);
void add_imgui_clipboard(sol::table&);
void add_imgui_color_editor(sol::table&);
void add_imgui_combo_box(sol::table&);
void add_imgui_common(sol::table&);
void add_imgui_disable(sol::table&);
void add_imgui_docking(sol::table&);
void add_imgui_drag_and_drop(sol::table&);
void add_imgui_drag_sliders(sol::table&);
void add_imgui_font(sol::table&);
void add_imgui_gui_io(sol::table&);
void add_imgui_images(sol::table&);
void add_imgui_keyboard_input(sol::table&);
void add_imgui_layout(sol::table&);
void add_imgui_list_clipper(sol::table&);
void add_imgui_menu(sol::table&);
void add_imgui_mouse_input(sol::table&);
void add_imgui_param_stacks(sol::table&, version_number version);
void add_imgui_popup(sol::table&);
void add_imgui_regular_sliders(sol::table&);
void add_imgui_scopes(sol::table&);
void add_imgui_style(sol::table&);
void add_imgui_tables(sol::table&);
void add_imgui_tabs(sol::table&);
void add_imgui_text(sol::table&);
void add_imgui_text_input(sol::table&);
void add_imgui_tooltips(sol::table&);
void add_imgui_trees(sol::table&);
void add_imgui_version_info(sol::state_view, sol::table&);
void add_imgui_viewports(sol::table&);
void add_imgui_widget_utils(sol::table&);
void add_imgui_widgets_main(sol::table&);
void add_imgui_windows(sol::table&, version_number version);
void add_implot(sol::state_view, sol::table&);

sol::table load_imgui(sol::this_state s, sol::table load_params)
{
    std::string version_str = load_params["version"];
    std::string mod_name = load_params["mod"];

    auto parsed_version = version_number::from_string(version_str);
    if (!parsed_version) {
        report_incompatibility(mod_name, version_str, incompatibility_reason::cant_parse_version);
    } else if (!version_compatible(ndi::version, parsed_version.value())) {
        report_incompatibility(mod_name, version_str, incompatibility_reason::version_mismatch);
    }

    auto version = parsed_version.value_or(ndi::version).zero_fill();

    std::cout << "load_imgui: '" << mod_name << "' requested noita imgui version " << version << '\n';

    sol::state_view lua{s};
    sol::table imgui = lua.create_table();

    add_container(imgui);
    add_imgui_clipboard(imgui);
    add_imgui_color_editor(imgui);
    add_imgui_combo_box(imgui);
    add_imgui_common(imgui);
    add_imgui_disable(imgui);
    add_imgui_docking(imgui);
    add_imgui_drag_and_drop(imgui);
    add_imgui_drag_sliders(imgui);
    add_imgui_font(imgui);
    add_imgui_gui_io(imgui);
    add_imgui_images(imgui);
    add_imgui_keyboard_input(imgui);
    add_imgui_layout(imgui);
    add_imgui_list_clipper(imgui);
    add_imgui_menu(imgui);
    add_imgui_mouse_input(imgui);
    add_imgui_param_stacks(imgui, version);
    add_imgui_popup(imgui);
    add_imgui_regular_sliders(imgui);
    add_imgui_scopes(imgui);
    add_imgui_style(imgui);
    add_imgui_tables(imgui);
    add_imgui_tabs(imgui);
    add_imgui_text(imgui);
    add_imgui_text_input(imgui);
    add_imgui_tooltips(imgui);
    add_imgui_trees(imgui);
    add_imgui_version_info(lua, imgui);
    add_imgui_viewports(imgui);
    add_imgui_widget_utils(imgui);
    add_imgui_widgets_main(imgui);
    add_imgui_windows(imgui, version);
    add_implot(lua, imgui);

    return imgui;
}

extern "C"
NOITA_DEAR_IMGUI_EXPORT void add_lua_features(lua_State* L, const std::vector<std::string>& names)
{
    sol::state_view lua{L};
    for (auto& name : names) {
        lua.set_function("load_" + name, load_imgui);
    }
}
