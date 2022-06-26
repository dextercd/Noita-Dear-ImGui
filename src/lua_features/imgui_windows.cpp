#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

// imgui.h contains the following disclaimer:
// [Important: due to legacy reason, this is inconsistent with most other functions such as BeginMenu/EndMenu,
// BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding BeginXXX function
// returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
//
// Instead of waiting for ImGui to fix this and having mods break, let's make
// this change right now in the Noita bindings.

bool ConsistentBegin(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0)
{
    auto visible = ImGui::Begin(name, p_open, flags);
    if (!visible)
        ImGui::End();

    return visible;
}

bool ConsistentBeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0)
{
    auto visible = ImGui::BeginChild(str_id, size, border, flags);
    if (!visible)
        ImGui::EndChild();

    return visible;
}

void add_imgui_windows(sol::table& imgui)
{
    imgui.new_enum("WindowFlags",
        "None",                      ImGuiWindowFlags_None,
        "NoTitleBar",                ImGuiWindowFlags_NoTitleBar,
        "NoResize",                  ImGuiWindowFlags_NoResize,
        "NoMove",                    ImGuiWindowFlags_NoMove,
        "NoScrollbar",               ImGuiWindowFlags_NoScrollbar,
        "NoScrollWithMouse",         ImGuiWindowFlags_NoScrollWithMouse,
        "NoCollapse",                ImGuiWindowFlags_NoCollapse,
        "AlwaysAutoResize",          ImGuiWindowFlags_AlwaysAutoResize,
        "NoBackground",              ImGuiWindowFlags_NoBackground,
        "NoSavedSettings",           ImGuiWindowFlags_NoSavedSettings,
        "NoMouseInputs",             ImGuiWindowFlags_NoMouseInputs,
        "MenuBar",                   ImGuiWindowFlags_MenuBar,
        "HorizontalScrollbar",       ImGuiWindowFlags_HorizontalScrollbar,
        "NoFocusOnAppearing",        ImGuiWindowFlags_NoFocusOnAppearing,
        "NoBringToFrontOnFocus",     ImGuiWindowFlags_NoBringToFrontOnFocus,
        "AlwaysVerticalScrollbar",   ImGuiWindowFlags_AlwaysVerticalScrollbar,
        "AlwaysHorizontalScrollbar", ImGuiWindowFlags_AlwaysHorizontalScrollbar,
        "AlwaysUseWindowPadding",    ImGuiWindowFlags_AlwaysUseWindowPadding,
        "NoNavInputs",               ImGuiWindowFlags_NoNavInputs,
        "NoNavFocus",                ImGuiWindowFlags_NoNavFocus,
        "UnsavedDocument",           ImGuiWindowFlags_UnsavedDocument,
        "NoNav",                     ImGuiWindowFlags_NoNav,
        "NoDecoration",              ImGuiWindowFlags_NoDecoration,
        "NoInputs",                  ImGuiWindowFlags_NoInputs
    );

    // Windows
    imgui.set_function("Begin",
        sol::overload(
            [](const char* name) { return ConsistentBegin(name); },
            [](const char* name, bool open) { auto ret = ConsistentBegin(name, &open); return std::tuple{ret, open}; },
            [](const char* name, bool open, ImGuiWindowFlags flags) { auto ret = ConsistentBegin(name, &open, flags); return std::tuple{ret, open}; }));
    imgui.set_function("End", &ImGui::End);

    // Child Windows
    imgui.set_function("BeginChild",
        sol::overload(
            [](const char* str_id) { return ConsistentBeginChild(str_id); },
            [](const char* str_id, float size_x, float size_y) { return ConsistentBeginChild(str_id, {size_x, size_y}); },
            [](const char* str_id, float size_x, float size_y, bool border) { return ConsistentBeginChild(str_id, {size_x, size_y}, border); },
            [](const char* str_id, float size_x, float size_y, bool border, ImGuiWindowFlags flags) { return ConsistentBeginChild(str_id, {size_x, size_y}, border, flags); }));
    imgui.set_function("EndChild", &ImGui::EndChild);

    // Windows Utilities
    imgui.set_function("IsWindowAppearing", &ImGui::IsWindowAppearing);
    imgui.set_function("IsWindowCollapsed", &ImGui::IsWindowCollapsed);
    imgui.set_function("IsWindowFocused",
        sol::overload(
            []() { return ImGui::IsWindowFocused(); },
            &ImGui::IsWindowFocused));
    imgui.set_function("IsWindowHovered",
        sol::overload(
            []() { return ImGui::IsWindowHovered(); },
            &ImGui::IsWindowHovered));
    imgui.set_function("GetWindowDrawList", &ImGui::GetWindowDrawList);
    imgui.set_function("GetWindowPos", &ImGui::GetWindowPos);
    imgui.set_function("GetWindowSize", &ImGui::GetWindowSize);
    imgui.set_function("GetWindowWidth", &ImGui::GetWindowWidth);
    imgui.set_function("GetWindowHeight", &ImGui::GetWindowHeight);

    // Window manipulation
    imgui.set_function("SetNextWindowPos",
        sol::overload(
            [](float pos_x, float pos_y) { return ImGui::SetNextWindowPos({pos_x, pos_y}); },
            [](float pos_x, float pos_y, ImGuiCond cond) { return ImGui::SetNextWindowPos({pos_x, pos_y}, cond); },
            &ImGui::SetNextWindowPos));
    imgui.set_function("SetNextWindowSize",
        sol::overload(
            [](float size_x, float size_y) { return ImGui::SetNextWindowSize({size_x, size_y}); },
            &ImGui::SetNextWindowSize));
    //imgui.set_function("SetNextWindowSizeConstraints", &ImGui::SetNextWindowSizeConstraints);
    imgui.set_function("SetNextWindowContentSize", &ImGui::SetNextWindowContentSize);
    imgui.set_function("SetNextWindowCollapsed",
        sol::overload(
            [](bool collapsed) { return ImGui::SetNextWindowCollapsed(collapsed); },
            &ImGui::SetNextWindowCollapsed));
    imgui.set_function("SetNextWindowFocus", &ImGui::SetNextWindowFocus);
    imgui.set_function("SetNextWindowBgAlpha", &ImGui::SetNextWindowBgAlpha);
    imgui.set_function("SetWindowPos",
        sol::overload(
            [](float pos_x, float pos_y) { return ImGui::SetWindowPos({pos_x, pos_y}); },
            [](float pos_x, float pos_y, ImGuiCond cond) { return ImGui::SetWindowPos({pos_x, pos_y}, cond); },
            [](const char* name, float pos_x, float pos_y) { return ImGui::SetWindowPos(name, {pos_x, pos_y}); },
            [](const char* name, float pos_x, float pos_y, ImGuiCond cond) { return ImGui::SetWindowPos(name, {pos_x, pos_y}, cond); }));
    imgui.set_function("SetWindowSize",
        sol::overload(
            [](float pos_x, float pos_y) { return ImGui::SetWindowSize({pos_x, pos_y}); },
            [](float pos_x, float pos_y, ImGuiCond cond) { return ImGui::SetWindowSize({pos_x, pos_y}, cond); },
            [](const char* name, float pos_x, float pos_y) { return ImGui::SetWindowSize(name, {pos_x, pos_y}); },
            [](const char* name, float pos_x, float pos_y, ImGuiCond cond) { return ImGui::SetWindowSize(name, {pos_x, pos_y}, cond); }));
    imgui.set_function("SetWindowCollapsed",
        sol::overload(
            [](bool collapsed) { return ImGui::SetWindowCollapsed(collapsed); },
            [](bool collapsed, ImGuiCond cond) { return ImGui::SetWindowCollapsed(collapsed, cond); },
            [](const char* name, bool collapsed) { return ImGui::SetWindowCollapsed(name, collapsed); },
            [](const char* name, bool collapsed, ImGuiCond cond) { return ImGui::SetWindowCollapsed(name, collapsed, cond); }));
    imgui.set_function("SetWindowFocus",
        sol::overload(
            sol::resolve<void()>(ImGui::SetWindowFocus),
            sol::resolve<void(const char*)>(ImGui::SetWindowFocus)));

    // Content region
    imgui.set_function("GetContentRegionAvail", &ImGui::GetContentRegionAvail);
    imgui.set_function("GetContentRegionMax", &ImGui::GetContentRegionMax);
    imgui.set_function("GetWindowContentRegionMin", &ImGui::GetWindowContentRegionMin);
    imgui.set_function("GetWindowContentRegionMax", &ImGui::GetWindowContentRegionMax);

    // Windows Scrolling
    imgui.set_function("GetScrollX", &ImGui::GetScrollX);
    imgui.set_function("GetScrollY", &ImGui::GetScrollY);
    imgui.set_function("SetScrollX", &ImGui::SetScrollX);
    imgui.set_function("SetScrollY", &ImGui::SetScrollY);
    imgui.set_function("GetScrollMaxX", &ImGui::GetScrollMaxX);
    imgui.set_function("GetScrollMaxY", &ImGui::GetScrollMaxY);
    imgui.set_function("SetScrollHereX",
        sol::overload(
            []() { return ImGui::SetScrollHereX(); },
            &ImGui::SetScrollHereX));
    imgui.set_function("SetScrollHereY",
        sol::overload(
            []() { return ImGui::SetScrollHereY(); },
            &ImGui::SetScrollHereY));
    imgui.set_function("SetScrollFromPosX",
        sol::overload(
            [](float local_x) { return ImGui::SetScrollFromPosX(local_x); },
            &ImGui::SetScrollFromPosX));
    imgui.set_function("SetScrollFromPosY",
        sol::overload(
            [](float local_y) { return ImGui::SetScrollFromPosY(local_y); },
            &ImGui::SetScrollFromPosY));
}
