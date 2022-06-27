#ifndef NOITA_IMGUI_HOOK_POINTS_HPP
#define NOITA_IMGUI_HOOK_POINTS_HPP

#include <optional>

struct hook_points {
    void* sdl_pollevent;
    void* sdl_gl_swapwindow;
    void* lual_newstate;

    bool complete() const
    {
        return sdl_pollevent && sdl_gl_swapwindow && lual_newstate;
    }
};

std::optional<hook_points> get_hook_points_for_exe(const char* path);

#endif // header guard
