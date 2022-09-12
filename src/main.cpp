#include <iostream>
#include <memory>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <MinHook.h>

#include <noita_imgui/add_lua_features.hpp>
#include <noita_dear_imgui_export.h>
#include "style.hpp"
#include "version_compat_window.hpp"

bool imgui_initialised = false;

// GLSL version used in Noita's shaders
char glsl_version[] = "#version 110";

void setup_imgui(SDL_Window* window, SDL_GLContext gl_context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    noita_imgui_style();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        throw std::runtime_error{"Couldn't init ImGui OpenGL3"};
    }

    io.Fonts->AddFontFromFileTTF("mods/NoitaDearImGui/NoitaPixel.ttf", 20);
    io.Fonts->AddFontDefault();

    imgui_initialised = true;
}

bool have_frame = false;

void start_frame()
{
    if (have_frame)
        return;

    have_frame = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    show_version_compat_window();
}

void render()
{
    if (!imgui_initialised) {
        auto window = SDL_GL_GetCurrentWindow();
        auto gl_context = SDL_GL_GetCurrentContext();
        setup_imgui(window, gl_context);
        start_frame();
    }

    if (!have_frame)
        return;

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    have_frame = false;
    start_frame();
}

using SDL_GL_SwapWindow_f = void (*)(SDL_Window*);

SDL_GL_SwapWindow_f original_SDL_GL_SwapWindow = nullptr;

void SDL_GL_SwapWindow_hook(SDL_Window* ctx)
{
    render();
    return original_SDL_GL_SwapWindow(ctx);
}

using SDL_PollEvent_f = int(*)(SDL_Event* event);
SDL_PollEvent_f original_SDL_PollEvent = nullptr;

bool is_mouse_event(SDL_Event* event)
{
    switch (event->type) {
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
            return true;
    }

    return false;
}

bool is_keyboard_event(SDL_Event* event)
{
    switch (event->type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            return true;
    }

    return false;
}

// Cursor state, used to restore old cursor settings when you move your mouse
// off all ImGui windows.
SDL_Cursor* restore_cursor = nullptr;
bool restore_show_cursor = false;

bool previous_want_capture_mouse = false;

int SDL_PollEvent_hook(SDL_Event* event)
{
    auto ret = original_SDL_PollEvent(event);

    if (imgui_initialised && event && ret) {
        ImGui_ImplSDL2_ProcessEvent(event);

        auto& io = ImGui::GetIO();

        if (!previous_want_capture_mouse && io.WantCaptureMouse) {
            restore_cursor = SDL_GetCursor();
            restore_show_cursor = SDL_ShowCursor(SDL_ENABLE);
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
        } else if (previous_want_capture_mouse && !io.WantCaptureMouse) {
            io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
            SDL_ShowCursor(restore_show_cursor);
            if (restore_cursor) {
                SDL_SetCursor(restore_cursor);
            }
        }

        previous_want_capture_mouse = io.WantCaptureMouse;

        if (io.WantCaptureMouse && is_mouse_event(event))
            return SDL_PollEvent_hook(event);

        if (io.WantCaptureKeyboard && is_keyboard_event(event))
            return SDL_PollEvent_hook(event);
    }

    return ret;
}

using luaL_newstate_f = lua_State*(*)();
luaL_newstate_f original_luaL_newstate;

lua_State* luaL_newstate_hook()
{
    auto state = original_luaL_newstate();
    add_lua_features(state);
    return state;
}

struct hook {
    void* function;
    void* hook_function;
    void** original;

    hook(void* f, void* h, void** o)
        : function{f}
        , hook_function{h}
        , original{o}
    {
        if (MH_CreateHook(function, hook_function, original) != MH_OK) {
            throw std::runtime_error{"Couldn't install hook."};
        }

        if (MH_EnableHook(function) != MH_OK) {
            throw std::runtime_error{"Couldn't enable hook."};
        }
    }

    ~hook()
    {
        MH_RemoveHook(function);
    }
};

struct imgui_hooks {
    hook sdl_pollevent;
    hook sdl_gl_swapwindow;
    hook lual_newstate;

    imgui_hooks(void* pollevent, void* swapwindow, void* newstate)
        : sdl_pollevent{
            pollevent,
            SDL_PollEvent_hook,
            reinterpret_cast<void**>(&original_SDL_PollEvent)}
        , sdl_gl_swapwindow{
            swapwindow,
            SDL_GL_SwapWindow_hook,
            reinterpret_cast<void**>(&original_SDL_GL_SwapWindow)}
        , lual_newstate{
            newstate,
            luaL_newstate_hook,
            reinterpret_cast<void**>(&original_luaL_newstate)}
    {
    }
};

std::unique_ptr<imgui_hooks> imgui_hooks_lifetime;

extern "C"
NOITA_DEAR_IMGUI_EXPORT void init_imgui(void* pollevent, void* swapwindow, void* newstate)
{
    if (imgui_hooks_lifetime)
        return;

    if (MH_Initialize() != MH_OK) {
        std::cerr << "MH_Initialize failed.\n";
        return;
    }

    char file_name_buffer[1024];
    if (GetModuleFileNameA(nullptr, file_name_buffer, sizeof(file_name_buffer)) == 0) {
        std::cerr << "Couldn't get Noita executable file name! Could not initialise hooks for ImGui\n";
        return;
    }

    std::cout << "Initialising ImGui hook points.\n";
    imgui_hooks_lifetime = std::make_unique<imgui_hooks>(
        pollevent, swapwindow, newstate
    );
}
