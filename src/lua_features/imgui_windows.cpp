#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_windows(sol::table& imgui)
{
    // Windows
    imgui.set_function("Begin",
        sol::overload(
            [](const char* name) { return ImGui::Begin(name); },
            [](const char* name, bool open) { auto ret = ImGui::Begin(name, &open); return std::tuple{ret, open}; },
            [](const char* name, bool open, ImGuiWindowFlags flags) { auto ret = ImGui::Begin(name, &open, flags); return std::tuple{ret, open}; }));
    imgui.set_function("End", &ImGui::End);

    // Child Windows
    imgui.set_function("BeginChild",
        sol::overload(
            [](const char* str_id) { return ImGui::BeginChild(str_id); },
            [](const char* str_id, ImVec2 size) { return ImGui::BeginChild(str_id, size); },
            [](const char* str_id, ImVec2 size, bool border) { return ImGui::BeginChild(str_id, size, border); },
            [](const char* str_id, ImVec2 size, bool border, ImGuiWindowFlags flags) { return ImGui::BeginChild(str_id, size, border, flags); }));
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
            [](ImVec2 pos) { return ImGui::SetNextWindowPos(pos); },
            [](ImVec2 pos, ImGuiCond cond) { return ImGui::SetNextWindowPos(pos, cond); },
            &ImGui::SetNextWindowPos));
    imgui.set_function("SetNextWindowSize",
        sol::overload(
            [](ImVec2 size) { return ImGui::SetNextWindowSize(size); },
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
            [](ImVec2 pos) { return ImGui::SetWindowPos(pos); },
            [](ImVec2 pos, ImGuiCond cond) { return ImGui::SetWindowPos(pos, cond); },
            [](const char* name, ImVec2 pos) { return ImGui::SetWindowPos(name, pos); },
            [](const char* name, ImVec2 pos, ImGuiCond cond) { return ImGui::SetWindowPos(name, pos, cond); }));
    imgui.set_function("SetWindowSize",
        sol::overload(
            [](ImVec2 pos) { return ImGui::SetWindowSize(pos); },
            [](ImVec2 pos, ImGuiCond cond) { return ImGui::SetWindowSize(pos, cond); },
            [](const char* name, ImVec2 pos) { return ImGui::SetWindowSize(name, pos); },
            [](const char* name, ImVec2 pos, ImGuiCond cond) { return ImGui::SetWindowSize(name, pos, cond); }));
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
