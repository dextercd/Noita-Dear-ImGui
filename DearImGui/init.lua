local ffi = require 'ffi'

ffi.cdef([[

void init_imgui();

void* LoadLibraryA(const char*);

]])

-- LuaJIT unloads a library once the `ffi.load` handle is garbage collected,
-- increase the library's reference count does not go below zero.
--
-- Without this, Noita crashes in JIT-ed Lua code when you use the "New Game"
-- option, probably because some Lua states are preserved across new runs.
assert(ffi.C.LoadLibraryA("mods/DearImGui/noita_dear_imgui.dll") ~= nil)

local dll = ffi.load("mods/DearImGui/noita_dear_imgui.dll")
dll.init_imgui()
