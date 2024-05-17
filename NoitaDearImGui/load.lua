-- Please don't change this file, this is purposefully careful to not load imgui
-- if the standalone version is installed.

local ffi = require("ffi")
local C = ffi.C

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

    void settings_imgui(
        bool viewports,
        bool navigation,
        int font_num,
        bool viewports_no_default_parent,
        int text_colour,
        float scale,
        bool pixel_no_anti_aliasing
    );
    void imgui_signal_unpause();

    int SetDllDirectoryA(const char* lpPathName);
    unsigned long GetDllDirectoryA(unsigned long nBufferLength, char* lpBuffer);
    void* LoadLibraryA(const char*);

    unsigned long GetLastError();

    int SDL_PollEvent(struct SDL_Event* event);
    void SDL_GL_SwapWindow(struct SDL_Window* window);
    struct lua_State* luaL_newstate();

    ]])

    local function loadlib_with_vs(vc_path, dll_path)
        local old_dll_dir_buf = ffi.new("char[256]")
        local old_dll_dir_sz = C.GetDllDirectoryA(ffi.sizeof(old_dll_dir_buf), old_dll_dir_buf)
        local old_dll_dir = nil
        if old_dll_dir_sz ~= 0 then
            old_dll_dir = ffi.string(old_dll_dir_buf, old_dll_dir_sz)
        end

        C.SetDllDirectoryA(vc_path)

        local hmodule = C.LoadLibraryA(dll_path)

        -- Restore to last dll directory. old_dll_dir may be nil, in that case
        -- SetDllDirectory changes to the default search order, which should be
        -- alright.
        C.SetDllDirectoryA(old_dll_dir)

        return hmodule
    end

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
    local hmodule = C.LoadLibraryA(imgui_dll_path)

    if hmodule == nil then
        -- Couldn't load the dll. This could be because they don't have the VC++
        -- redistributables installed globally. Try again but with our copy
        -- added to the search path.
        hmodule = loadlib_with_vs(path, imgui_dll_path)
    end

    if hmodule == nil then
        local err = C.GetLastError()
        error("ImGui load error: " .. err)
    end

    local imgui_dll = ffi.load(imgui_dll_path)
    local sdl = ffi.load("SDL2.dll")

    imgui_dll.init_imgui(
        false,
        path,
        name,
        sdl.SDL_PollEvent,
        sdl.SDL_GL_SwapWindow,
        C.luaL_newstate
    )

    return {
        imgui_dll = imgui_dll,
        settings_prefix = settings_prefix,
    }
end
