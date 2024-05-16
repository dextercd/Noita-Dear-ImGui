local imgui_ctx = dofile_once("mods/NoitaDearImGui/load.lua")("mods/NoitaDearImGui", "imgui")

local has_salakieli = ModIsEnabled("salakieli")

function setting_get(key)
    return ModSettingGet(imgui_ctx.settings_prefix .. key) or false
end

function configure_settings()
    local font_num = tonumber(setting_get("font")) or 0
    if font_num == 0 and has_salakieli then
        font_num = 5
    end
    imgui_ctx.imgui_dll.settings_imgui(
        setting_get("multi_viewports"),
        setting_get("navigation"),
        font_num,
        not setting_get("child_window_on_top"),
        tonumber(setting_get("text_colour"))
    )
end

configure_settings() -- Initial configure

-- Live preview
local pause_frame = 0
function OnPausePreUpdate()
    pause_frame = pause_frame + 1
    if pause_frame % 10 == 0 then
        configure_settings()
    end
end

function OnPausedChanged(is_paused, is_inventory_paused)
    -- Mod settings might've been changed
    configure_settings()

    if not is_paused and not is_inventory_paused then
        imgui_ctx.imgui_dll.imgui_signal_unpause()
    end
end
