local ffi = require 'ffi'

ffi.cdef([[

void init_imgui();

]])

local dll = ffi.load("mods/DearImGui/noita_dear_imgui.dll")
function OnPlayerSpawned( player_entity )
    dll.init_imgui()
end
