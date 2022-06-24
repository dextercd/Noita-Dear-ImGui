local ffi = require 'ffi'

ffi.cdef([[

void init_imgui();

void* LoadLibraryA(const char*);

]])

-- LuaJIT frees the OS library handle when the `ffi.load` handle is garbage
-- collected. We need to increase the library's reference count to prevent it
-- from getting unloaded.
--
-- Without this, Noita crashes in JIT-ed Lua code when you use the "New Game"
-- option, probably because some Lua states are preserved across new runs.
assert(ffi.C.LoadLibraryA("mods/NoitaDearImGui/noita_dear_imgui.dll") ~= nil)

local dll = ffi.load("mods/NoitaDearImGui/noita_dear_imgui.dll")
dll.init_imgui()
