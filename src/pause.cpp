#include <noita_dear_imgui_export.h>

#include <noita_imgui/pause.hpp>

bool just_unpaused = false;

extern "C"
NOITA_DEAR_IMGUI_EXPORT void imgui_signal_unpause()
{
    just_unpaused = true;
}

void imgui_clear_pause_state()
{
    just_unpaused = false;
}
