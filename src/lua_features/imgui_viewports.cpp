#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_viewports(sol::table& imgui)
{
    imgui.set_function("GetMainViewportID", []() { return ImGui::GetMainViewport()->ID; });
    imgui.set_function("GetMainViewportWorkPos",
        []() {
            auto viewport = ImGui::GetMainViewport();
            return std::tuple{viewport->WorkPos.x, viewport->WorkPos.y};
        });
    imgui.set_function("GetMainViewportPos",
        []() {
            auto viewport = ImGui::GetMainViewport();
            return std::tuple{viewport->Pos.x, viewport->Pos.y};
        });
    imgui.set_function("GetMainViewportSize",
        []() {
            auto viewport = ImGui::GetMainViewport();
            return std::tuple{viewport->Size.x, viewport->Size.y};
        });
    imgui.set_function("GetMainViewportWorkSize",
        []() {
            auto viewport = ImGui::GetMainViewport();
            return std::tuple{viewport->WorkSize.x, viewport->WorkSize.y};
        });
}
