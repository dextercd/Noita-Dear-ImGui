-- Please don't change this file, this is purposefully careful to not load imgui
-- if the standalone version is installed.

local ffi = require("ffi")

return function(path, name)
    local embedded_version = name ~= "imgui"
    if embedded_version and ModIsEnabled("NoitaDearImGui") then
        return nil
    end


    ffi.cdef([[

    void init_imgui(
        bool reset_ini,
        const char* path,
        const char* name,
        void* pollevent,
        void* swapwindow,
        void* newstate
    );

    void settings_imgui(bool viewports);

    void* LoadLibraryA(const char*);

    int SDL_PollEvent(struct SDL_Event* event);
    void SDL_GL_SwapWindow(struct SDL_Window* window);
    struct lua_State* luaL_newstate();

    ]])


    local settings_prefix = name .. ".imgui_"
    if not embedded_version then
        settings_prefix = "NoitaDearImGui."
    end

    function setting_get(key)
        return ModSettingGet(settings_prefix .. key) or false
    end


    local imgui_dll_path = path .. "/noita_dear_imgui.dll"
    if setting_get("build_type") == "debug" then
        imgui_dll_path = path .. "/Debug/noita_dear_imgui.dll"
    end

    -- LuaJIT frees the OS library handle when the `ffi.load` handle is garbage
    -- collected. We need to increase the library's reference count to prevent it
    -- from getting unloaded.
    --
    -- Without this, Noita crashes in JIT-ed Lua code when you use the "New Game"
    -- option, probably because some Lua states are preserved across new runs.
    assert(ffi.C.LoadLibraryA(imgui_dll_path) ~= nil)

    local imgui_dll = ffi.load(imgui_dll_path)
    local sdl = ffi.load("SDL2.dll")

    imgui_dll.init_imgui(
        false,
        path,
        name,
        sdl.SDL_PollEvent,
        sdl.SDL_GL_SwapWindow,
        ffi.C.luaL_newstate
    )

    return {
        imgui_dll = imgui_dll,
        settings_prefix = settings_prefix,
    }
end
