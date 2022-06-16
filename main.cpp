#include <iostream>

#include <lua.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <MinHook.h>

#include "noita_dear_imgui_export.h"

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
}

bool show_demo_window = true;

bool have_frame = false;

void start_frame()
{
    if (have_frame)
        return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
}

void render()
{
    if (!have_frame)
        return;

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    have_frame = false;
    start_frame();
}

using swap_window_f = void (__fastcall *)(void*);

swap_window_f original_swap_window;

void __fastcall swap_window_hook(void* ctx)
{
    std::cout << "Render called !\n" << std::flush;
    render();
    return original_swap_window(ctx);
}

extern "C"
NOITA_DEAR_IMGUI_EXPORT void init_imgui()
{
    if (MH_Initialize() != MH_OK) {
        return;
    }

    auto window = SDL_GL_GetCurrentWindow();
    auto gl_context = SDL_GL_GetCurrentContext();

    std::cout << "W:" << window << "\n" << std::flush;
    std::cout << "G:" << gl_context << "\n" << std::flush;

    setup_imgui(window, gl_context);

    start_frame();

    MH_CreateHook(
        reinterpret_cast<void*>(0xc37e80),
        swap_window_hook,
        reinterpret_cast<void**>(&original_swap_window));
    MH_EnableHook(reinterpret_cast<void*>(0xc37e80));
}

// 20:44
