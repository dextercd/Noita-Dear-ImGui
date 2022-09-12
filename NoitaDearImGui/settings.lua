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
        id = "multi_viewports",
        ui_name = "Multi viewports enabled",
        ui_description = "Support dragging ImGui windows outside the game window",
        value_default = false,
        scope = MOD_SETTING_SCOPE_RUNTIME,
    },
    {
        ui_fn = mod_setting_vertical_spacing,
        not_setting = true,
    },
    {
        ui_fn = mod_setting_warning,
        ui_name = "Viewports Warning",
        ui_description = "\n   You may experience issues when the game is full-screen.\n " ..
            "\n   This feature works best when 'Pause the game when unfocused' is" ..
            "\n   turned Off in [Game Settings > Input] (option at the bottom).",
        not_setting = true,
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
