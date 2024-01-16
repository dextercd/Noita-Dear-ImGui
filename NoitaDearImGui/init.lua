local imgui_ctx = dofile_once("mods/NoitaDearImGui/load.lua")("mods/NoitaDearImGui", "imgui")

function setting_get(key)
    return ModSettingGet(imgui_ctx.settings_prefix .. key) or false
end

function configure_settings()
    imgui_ctx.imgui_dll.settings_imgui(
        setting_get("multi_viewports"),
        setting_get("navigation"),
        tonumber(setting_get("font"))
    )
end

configure_settings() -- Initial configure

function OnPausedChanged(is_paused, is_inventory_paused)
    -- Mod settings might've been changed
    configure_settings()

    if not is_paused and not is_inventory_paused then
        imgui_ctx.imgui_dll.imgui_signal_unpause()
    end
end
