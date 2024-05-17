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
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include <implot.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <MinHook.h>

#include <noita_imgui/add_lua_features.hpp>
#include <noita_imgui/pause.hpp>
#include <noita_dear_imgui_export.h>

#include "style.hpp"
#include "fonts.hpp"
#include "version_compat_window.hpp"
#include "filesystem.hpp"
#include "image_loader.hpp"

bool is_embedded;
std::vector<std::string> load_names;
std::string mod_path;

// GLSL version used in Noita's shaders
const char glsl_version[] = "#version 110";

bool imgui_context_initialised = false;
bool imgui_backend_initialised = false;

bool style_initialised = false;

struct style_settings_t {
    float ui_scale = 1.0f;
    embedded_fonts default_font = embedded_fonts::noita_pixel;
    int text_colour = 0;
    bool pixel_no_anti_aliasing = true;

    friend bool operator==(const style_settings_t&, const style_settings_t&) = default;
};

style_settings_t style_settings;

int i = 0;
void load_style()
{
    auto new_style = ImGuiStyle{};
    noita_imgui_style(&new_style);
    new_style.ScaleAllSizes(style_settings.ui_scale);

    ImVec4 text_colour_options[] = {
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
        ImVec4(0.92f, 0.92f, 0.92f, 1.0f),
        ImVec4(0.86f, 0.86f, 0.86f, 1.0f),
    };

    if (style_settings.text_colour >= 0 && style_settings.text_colour < std::size(text_colour_options)) {
        new_style.Colors[ImGuiCol_Text] = text_colour_options[style_settings.text_colour];
    }

    ImGui::GetStyle() = new_style;

    ImGui_ImplOpenGL3_DestroyFontsTexture();

    add_fonts(mod_path, style_settings.ui_scale, style_settings.pixel_no_anti_aliasing);
    ImGuiIO& io = ImGui::GetIO();
    io.FontDefault = io.Fonts->Fonts[(int)style_settings.default_font];

    ImGui_ImplOpenGL3_CreateFontsTexture();
}

// Context is initialised as soon as the Noita mod is started
void init_imgui_context()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    imgui_context_initialised = true;
}

SDL_Window* main_window;

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

    main_window = window;
    imgui_backend_initialised = true;
}

void start_frame()
{
    if (!style_initialised) {
        style_initialised = true;
        load_style();
    }

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
    unload_unused_images();

    running_for_main_window = false;
}

using SDL_PollEvent_f = int(*)(SDL_Event* event);
SDL_PollEvent_f original_SDL_PollEvent = nullptr;

bool is_mouse_event(SDL_Event* event)
{
    switch (event->type) {
        // case SDL_MOUSEMOTION: Let through mouse motion events
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

// Bitmap tracking mouse button the game considers held. Used to prevent buttons
// from getting stuck.
std::uint32_t game_mouse_buttons_held = 0;

int SDL_PollEvent_hook(SDL_Event* event)
{
    auto ret = original_SDL_PollEvent(event);

    if (imgui_backend_initialised && event && ret) {
        ImGui_ImplSDL2_ProcessEvent(event);

        auto& io = ImGui::GetIO();
        if (is_mouse_event(event)) {
            if (event->type == SDL_MOUSEBUTTONUP && game_mouse_buttons_held & (1 << event->button.button)) {
                // Game thinks the button is down so we always return the button
                // release event to the game, even when io.WantCaptureMouse is
                // set so the button doesn't get stuck.
                goto return_event_to_game;
            }

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

        if (event->type == SDL_WINDOWEVENT &&
            event->window.event == SDL_WINDOWEVENT_CLOSE &&
            event->window.windowID == SDL_GetWindowID(main_window))
        {
            // Noita only has one window normally so it doesn't listen to close
            // events for its main window, it only listens for SDL_QUIT.
            // Translate the event here so closing the game window actually
            // works.
            event->type = SDL_QUIT;
        }
    }

return_event_to_game:
    if (event && ret) {
        if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
            auto button_bit = std::uint32_t{1} << event->button.button;

            if (event->type == SDL_MOUSEBUTTONDOWN)
                game_mouse_buttons_held |= button_bit;
            else
                game_mouse_buttons_held &= ~button_bit;
        }
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

    // Make sure filesystem is initialised early
    auto& fs = get_fs();

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
NOITA_DEAR_IMGUI_EXPORT void settings_imgui(
        bool viewports,
        bool navigation,
        int font_num,
        bool viewports_no_default_parent,
        int text_colour,
        float scale,
        bool pixel_no_anti_aliasing)
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

    style_settings_t new_settings;

    io.ConfigViewportsNoDefaultParent = viewports_no_default_parent;

    if (font_num >= 0 && font_num < (int)embedded_fonts::end_)
        new_settings.default_font = (embedded_fonts)font_num;

    new_settings.text_colour = text_colour;
    new_settings.ui_scale = scale;
    new_settings.pixel_no_anti_aliasing = pixel_no_anti_aliasing;

    if (new_settings != style_settings) {
        style_settings = new_settings;
        style_initialised = false;
    }
}
