local ffi = require 'ffi'

ffi.cdef([[

void init_imgui(void* pollevent, void* swapwindow, void* newstate);

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
    sdl.SDL_PollEvent,
    sdl.SDL_GL_SwapWindow,
    ffi.C.luaL_newstate
)
