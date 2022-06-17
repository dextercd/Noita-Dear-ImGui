local ffi = require 'ffi'

ffi.cdef([[

void init_imgui();

]])

local dll = ffi.load("mods/DearImGui/noita_dear_imgui.dll")
dll.init_imgui()
