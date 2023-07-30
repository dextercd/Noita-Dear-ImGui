#ifndef NOITA_IMGUI_IMGUI_CONFIG_HPP
#define NOITA_IMGUI_IMGUI_CONFIG_HPP

#include <noita_dear_imgui_export.h>

// Export ImGui functionality for any mods that don't use the Lua interface
#define IMGUI_API NOITA_DEAR_IMGUI_EXPORT
#define IMPLOT_API NOITA_DEAR_IMGUI_EXPORT

// https://github.com/epezent/implot#extremely-important-note
#define ImDrawIdx unsigned int

#endif // header guard
