-- Please don't change this file, this is purposefully careful to not load imgui
-- if the standalone version is installed.

local ffi = require("ffi")
local C = ffi.C

local non_virtual = {}
local function virtual_image_size(name, image)
    name = ffi.string(name)
    if  non_virtual[name] or
        name:sub(-4) ~= ".png" or
        ModImageWhoSetContent(name) == ""
    then
        return
    end

    local id, width, height = ModImageIdFromFilename(name)
    if id <= 0 then
        non_virtual[name] = true
        return
    end

    image[0], image[1], image[2] = id, width, height
end

local function virtual_image_data(id, width, height, data_out)
    for y=0,height-1 do
        for x=0,width-1 do
            local pixel = ModImageGetPixel(id, x, y)
            data_out[y * width + x] = pixel
        end
    end
end

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
        void* newstate,
        void (*virtual_image_size)(const char* name, int* image),
        void (*virtual_image_data)(int id, int width, int height, int* data_out)
    );

    void settings_imgui(
        bool viewports,
        bool navigation,
        int font_num,
        const char* noto_variant,
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
        local old_dll_dir_buf = ffi.new("char[1024]")
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
    function setting_set(key, value)
        return ModSettingSet(settings_prefix .. key, value)
    end
    function setting_set_next(key, value, is_default)
        return ModSettingSetNextValue(settings_prefix .. key, value, is_default)
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
    local hmodule = loadlib_with_vs(path, imgui_dll_path)

    if hmodule == nil then
        local err = C.GetLastError()
        error("ImGui load error: " .. err)
    end

    local imgui_dll = ffi.load(imgui_dll_path)
    local sdl = ffi.load("SDL2.dll")

    local reset_ini = setting_get("reset_ini") == "next_restart"

    imgui_dll.init_imgui(
        reset_ini,
        path,
        name,
        sdl.SDL_PollEvent,
        sdl.SDL_GL_SwapWindow,
        C.luaL_newstate,
        virtual_image_size,
        virtual_image_data
    )

    if reset_ini then
        setting_set("reset_ini", "no")
        setting_set_next("reset_ini", "no", false)
    end

    return {
        imgui_dll = imgui_dll,
        settings_prefix = settings_prefix,
    }
end
