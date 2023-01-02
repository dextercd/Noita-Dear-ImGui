#include <noita_dear_imgui_export.h>

extern bool just_unpaused;

extern "C"
NOITA_DEAR_IMGUI_EXPORT void imgui_signal_unpause();

void imgui_clear_pause_state();
