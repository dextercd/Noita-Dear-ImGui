local imgui_ctx = dofile_once("mods/NoitaDearImGui/load.lua")("mods/NoitaDearImGui", "imgui")

function setting_get(key)
    return ModSettingGet(imgui_ctx.settings_prefix .. key) or false
end

function configure_settings()
    imgui_ctx.imgui_dll.settings_imgui(setting_get("multi_viewports"))
end

configure_settings() -- Initial configure

function OnPausedChanged()
    -- Mod settings might've been changed
    configure_settings()
end
