dofile("data/scripts/lib/mod_settings.lua") -- see this file for documentation on some of the features.

local mod_id = "NoitaDearImGui"
mod_settings_version = 1

function mod_setting_warning(mod_id, gui, in_main_menu, im_id, setting)
    GuiColorSetForNextWidget(gui, 1.0, 0.4, 0.4, 1.0)
    GuiText(gui, mod_setting_group_x_offset, 0, setting.ui_name .. ": " .. setting.ui_description)
end

mod_settings =
{
    {
        category_id = "preferences",
        ui_name = "Preferences",
        ui_description = "User preferences",
        settings = {
            {
                id = "multi_viewports",
                ui_name = "Multi viewports enabled",
                ui_description = "Support dragging ImGui windows outside the game window",
                value_default = false,
                scope = MOD_SETTING_SCOPE_RUNTIME,
            },
            {
                ui_fn = mod_setting_warning,
                ui_name = "Viewports Warning",
                ui_description = "\n   You may experience issues when the game is full-screen.\n " ..
                    "\n   This feature works best when 'Pause the game when unfocused' is" ..
                    "\n   turned Off in [Game Settings > Input] (option at the bottom).",
                not_setting = true,
            },
            {
                ui_fn = mod_setting_vertical_spacing,
                not_setting = true,
            },
            {
                id = "navigation",
                ui_name = "Keyboard/Controller navigation",
                ui_description = "Allow focused windows to steal inputs from the game for navigating within the window.",
                value_default = false,
                scope = MOD_SETTING_SCOPE_RUNTIME,
            },
            {
                id = "font",
                ui_name = "Default font",
                ui_description = "Font used when not changed by UI code",
                value_default = "0",
                values = {
                    {"0", "Noita Pixel"},
                    {"3", "ImGui"},
                    {"4", "Monospace (Source Code Pro)"},
                },
                scope = MOD_SETTING_SCOPE_RUNTIME,
            },
            {
                id = "child_window_on_top",
                ui_name = "Keep child windows on top",
                ui_description = "Keep child windows always above game window. (Requires restart)",
                value_default = true,
                scope = MOD_SETTING_SCOPE_RUNTIME_RESTART,
            },
        },
    },

    {
        category_id = "for_developers",
        ui_name = "For Developers",
        ui_description = "Creating a mod that uses Dear ImGui? You may want to change these settings.",
        settings = {
            {
                id = "build_type",
                ui_name = "Build Type",
                ui_description = "Switch to debug build which has worse performance but better error reporting.\n"
                    .. "You must restart the game to apply this change.",
                value_default = "release",
                values = { {"release", "Release (optimised)"}, {"debug", "Debug (for devs)"}, },
                scope = MOD_SETTING_SCOPE_RUNTIME_RESTART,
            }
        },
    },
}

function ModSettingsUpdate(init_scope)
    mod_settings_update(mod_id, mod_settings, init_scope)
end

function ModSettingsGuiCount()
    return mod_settings_gui_count(mod_id, mod_settings)
end

function ModSettingsGui(gui, in_main_menu)
    mod_settings_gui(mod_id, mod_settings, gui, in_main_menu)
end
