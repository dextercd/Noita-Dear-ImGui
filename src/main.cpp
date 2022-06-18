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

#include "add_lua_features.hpp"
#include "noita_dear_imgui_export.h"

bool imgui_initialised = false;

// GLSL version used in Noita's shaders
char glsl_version[] = "#version 110";

void setup_imgui(SDL_Window* window, SDL_GLContext gl_context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();
    
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    imgui_initialised = true;
}

bool show_demo_window = true;

bool have_frame = false;

void start_frame()
{
    if (have_frame)
        return;
    have_frame = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
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

using swap_window_f = void (__fastcall *)(void*);

swap_window_f original_swap_window = nullptr;

void __fastcall swap_window_hook(void* ctx)
{
    render();
    return original_swap_window(ctx);
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

int SDL_PollEvent_hook(SDL_Event* event)
{
    auto ret = original_SDL_PollEvent(event);

    if (imgui_initialised && event && ret) {
        ImGui_ImplSDL2_ProcessEvent(event);

        auto& io = ImGui::GetIO();
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
    hook sdl_pollevent{
        *reinterpret_cast<void**>(0xd1e620),
        SDL_PollEvent_hook,
        reinterpret_cast<void**>(&original_SDL_PollEvent)
    };

    hook swap_window{
        reinterpret_cast<void*>(0xc37e80),
        swap_window_hook,
        reinterpret_cast<void**>(&original_swap_window)
    };

    hook lual_newstate{
        *reinterpret_cast<void**>(0xd1e7b0),
        luaL_newstate_hook,
        reinterpret_cast<void**>(&original_luaL_newstate)
    };
};

std::unique_ptr<imgui_hooks> imgui_hooks_lifetime;

extern "C"
NOITA_DEAR_IMGUI_EXPORT void init_imgui()
{
    if (imgui_hooks_lifetime)
        return;

    if (MH_Initialize() != MH_OK) {
        std::cerr << "MH_Initialize failed.\n";
        return;
    }

    imgui_hooks_lifetime = std::make_unique<imgui_hooks>();
}
