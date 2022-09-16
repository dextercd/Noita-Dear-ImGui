local ffi = require 'ffi'

local mod_id = "NoitaDearImGui"
function setting_get(name)
    return ModSettingGet(mod_id .. "." .. name)
end

ffi.cdef([[

void init_imgui(bool reset_ini, void* pollevent, void* swapwindow, void* newstate);
void settings_imgui(bool viewports);

void* LoadLibraryA(const char*);

int SDL_PollEvent(struct SDL_Event* event);
void SDL_GL_SwapWindow(struct SDL_Window* window);
struct lua_State* luaL_newstate();

]])

-- LuaJIT frees the OS library handle when the `ffi.load` handle is garbage
-- collected. We need to increase the library's reference count to prevent it
-- from getting unloaded.
--
-- Without this, Noita crashes in JIT-ed Lua code when you use the "New Game"
-- option, probably because some Lua states are preserved across new runs.
assert(ffi.C.LoadLibraryA("mods/NoitaDearImGui/noita_dear_imgui.dll") ~= nil)

local dll = ffi.load("mods/NoitaDearImGui/noita_dear_imgui.dll")
local sdl = ffi.load("SDL2.dll")

dll.init_imgui(
    false,
    sdl.SDL_PollEvent,
    sdl.SDL_GL_SwapWindow,
    ffi.C.luaL_newstate
)

function configure_settings()
    dll.settings_imgui(setting_get("multi_viewports"))
end

configure_settings() -- Initial configure

function OnPausedChanged()
    -- Mod settings might've been changed
    configure_settings()
end
