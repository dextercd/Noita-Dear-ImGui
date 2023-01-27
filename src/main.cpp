#include <iostream>
#include <memory>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
#include <noita_imgui/pause.hpp>
#include <noita_dear_imgui_export.h>
#include "style.hpp"
#include "version_compat_window.hpp"

bool is_embedded;
std::vector<std::string> load_names;
std::string mod_path;

// GLSL version used in Noita's shaders
char glsl_version[] = "#version 110";

bool imgui_context_initialised = false;
bool imgui_backend_initialised = false;

// Context is initialised as soon as the Noita mod is started
void init_imgui_context()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    noita_imgui_style();
    auto font_path = mod_path + "/NoitaPixel.ttf";

    ImVector<ImWchar> ranges;
    ImFontGlyphRangesBuilder builder;
    builder.AddChar(0x2013); // EN DASH
    builder.AddChar(0x2014); // EM DASH
    builder.AddChar(0x2019); // RIGHT SINGLE QUOTATION MARK
    builder.AddChar(0x201c); // LEFT DOUBLE QUOTATION MARK
    builder.AddChar(0x201d); // RIGHT DOUBLE QUOTATION MARK
    builder.AddChar(0x201e); // DOUBLE LOW-9 QUOTATION MARK
    builder.AddChar(0x2026); // HORIZONTAL ELLIPSIS
    builder.AddChar(0x221e); // INFINITY
    ImWchar latin_extended_a[]{0x100, 0x17f, 0};
    builder.AddRanges(latin_extended_a);
    builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic());  // Includes default ranges
    builder.BuildRanges(&ranges);

    io.Fonts->AddFontFromFileTTF(font_path.c_str(), 20, nullptr, ranges.Data);
    io.Fonts->AddFontFromFileTTF(font_path.c_str(), 28, nullptr, ranges.Data);
    io.Fonts->AddFontFromFileTTF(font_path.c_str(), 36, nullptr, ranges.Data);
    io.Fonts->AddFontDefault();
    io.Fonts->Build();  // Build with ranges in scope

    imgui_context_initialised = true;
}

// Backend is initialised at the first swapwindow call after the context is
// initialised.
void setup_imgui_backend(SDL_Window* window, SDL_GLContext gl_context)
{
    ImGuiIO& io = ImGui::GetIO();

    // Need to have this enabled during platform init so this can be enabled/
    // disabled dynamically
    auto restore_flags = io.ConfigFlags;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        throw std::runtime_error{"Couldn't init ImGui OpenGL3"};
    }

    io.ConfigFlags = restore_flags;

    imgui_backend_initialised = true;
}

void start_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    show_version_compat_window();
}

void render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();

    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }

    // Reset pause status for next frame
    imgui_clear_pause_state();
}

using SDL_GL_SwapWindow_f = void (*)(SDL_Window*);

SDL_GL_SwapWindow_f original_SDL_GL_SwapWindow = nullptr;


bool running_for_main_window = false;

void SDL_GL_SwapWindow_hook(SDL_Window* ctx)
{
    // RenderPlatformWindowsDefault will also call swapwindow, which makes this
    // function recursive. We have to guard against that.
    // Don't do anything special if this function is /already/ running for the
    // main window.
    if (running_for_main_window)
        return original_SDL_GL_SwapWindow(ctx);

    if (!imgui_context_initialised)
        return original_SDL_GL_SwapWindow(ctx);

    if (imgui_context_initialised && !imgui_backend_initialised) {
        auto window = SDL_GL_GetCurrentWindow();
        auto gl_context = SDL_GL_GetCurrentContext();
        setup_imgui_backend(window, gl_context);
        start_frame();
    }

    running_for_main_window = true;

    render();
    original_SDL_GL_SwapWindow(ctx);
    start_frame();

    running_for_main_window = false;
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
        //case SDL_KEYUP: -- allow key up events so the game doesn't think the key is 'stuck'
            return true;
    }

    return false;
}

int SDL_PollEvent_hook(SDL_Event* event)
{
    // Cursor state, used to restore old cursor settings when you move your mouse
    // off all ImGui windows.
    static SDL_Cursor* restore_cursor = nullptr;
    static bool restore_show_cursor = false;

    static bool previous_want_capture_mouse = false;
    static bool previous_want_capture_keyboard = false;

    auto ret = original_SDL_PollEvent(event);

    if (imgui_backend_initialised && event && ret) {
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
        previous_want_capture_keyboard = io.WantCaptureKeyboard;

        if (is_mouse_event(event)) {
            if (io.WantCaptureMouse)
                return SDL_PollEvent_hook(event);

            if (event->type == SDL_MOUSEBUTTONDOWN && io.WantCaptureKeyboard) {
                // The player should be able to restore the game's keyboard access
                // by clicking outside of any imgui window. When they do this it
                // shouldn't fire a wand or throw a flask.
                return SDL_PollEvent_hook(event);
            }
        }

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
    add_lua_features(state, load_names);
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
            (void*)SDL_PollEvent_hook,
            reinterpret_cast<void**>(&original_SDL_PollEvent)}
        , sdl_gl_swapwindow{
            swapwindow,
            (void*)SDL_GL_SwapWindow_hook,
            reinterpret_cast<void**>(&original_SDL_GL_SwapWindow)}
        , lual_newstate{
            newstate,
            (void*)luaL_newstate_hook,
            reinterpret_cast<void**>(&original_luaL_newstate)}
    {
    }
};

std::unique_ptr<imgui_hooks> imgui_hooks_lifetime;

bool is_loaded()
{
    return (bool)imgui_hooks_lifetime;
}

extern "C"
NOITA_DEAR_IMGUI_EXPORT void init_imgui(
        bool reset_ini,
        const char* path,
        const char* name,
        void* pollevent,
        void* swapwindow,
        void* newstate)
{
    if (!is_loaded() || is_embedded)
        load_names.push_back(name);

    if (is_loaded())
        return;

    is_embedded = std::string_view{name} != "imgui";
    if (is_embedded) {
        mod_path = path;
    } else {
        mod_path = "mods/NoitaDearImGui";
        // No lying!
        auto attrs = GetFileAttributesA(mod_path.c_str());
        if (attrs == INVALID_FILE_ATTRIBUTES) {
            auto error = GetLastError();
            if (error == ERROR_INVALID_NAME || error == ERROR_FILE_NOT_FOUND)
                ExitProcess(666);
        }
    }

    if (MH_Initialize() != MH_OK) {
        std::cerr << "MH_Initialize failed.\n";
        return;
    }

    std::cout << "Initialising ImGui hook points.\n";
    imgui_hooks_lifetime = std::make_unique<imgui_hooks>(
        pollevent, swapwindow, newstate
    );

    init_imgui_context();

    // Loading an empty ini will prevent ImGui from loading from the file
    if (reset_ini)
        ImGui::LoadIniSettingsFromMemory("", 0);
}

extern "C"
NOITA_DEAR_IMGUI_EXPORT void settings_imgui(bool viewports, bool navigation)
{
    if (!imgui_context_initialised)
        return;

    ImGuiConfigFlags turn_on{};
    ImGuiConfigFlags turn_off{};

    (viewports ? turn_on : turn_off) |= ImGuiConfigFlags_ViewportsEnable;

    (navigation ? turn_on : turn_off) |= ImGuiConfigFlags_NavEnableKeyboard;
    (navigation ? turn_on : turn_off) |= ImGuiConfigFlags_NavEnableGamepad;
    (navigation ? turn_off : turn_on) |= ImGuiConfigFlags_NavNoCaptureKeyboard;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= turn_on;
    io.ConfigFlags &= ~turn_off;
}
