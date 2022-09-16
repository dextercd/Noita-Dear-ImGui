#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_popup(sol::table& imgui)
{
    imgui.new_enum<ImGuiPopupFlags>("PopupFlags", {
        {"None",                      ImGuiWindowFlags_None},
        {"NoTitleBar",                ImGuiWindowFlags_NoTitleBar},
        {"NoResize",                  ImGuiWindowFlags_NoResize},
        {"NoMove",                    ImGuiWindowFlags_NoMove},
        {"NoScrollbar",               ImGuiWindowFlags_NoScrollbar},
        {"NoScrollWithMouse",         ImGuiWindowFlags_NoScrollWithMouse},
        {"NoCollapse",                ImGuiWindowFlags_NoCollapse},
        {"AlwaysAutoResize",          ImGuiWindowFlags_AlwaysAutoResize},
        {"NoBackground",              ImGuiWindowFlags_NoBackground},
        {"NoSavedSettings",           ImGuiWindowFlags_NoSavedSettings},
        {"NoMouseInputs",             ImGuiWindowFlags_NoMouseInputs},
        {"MenuBar",                   ImGuiWindowFlags_MenuBar},
        {"HorizontalScrollbar",       ImGuiWindowFlags_HorizontalScrollbar},
        {"NoFocusOnAppearing",        ImGuiWindowFlags_NoFocusOnAppearing},
        {"NoBringToFrontOnFocus",     ImGuiWindowFlags_NoBringToFrontOnFocus},
        {"AlwaysVerticalScrollbar",   ImGuiWindowFlags_AlwaysVerticalScrollbar},
        {"AlwaysHorizontalScrollbar", ImGuiWindowFlags_AlwaysHorizontalScrollbar},
        {"AlwaysUseWindowPadding",    ImGuiWindowFlags_AlwaysUseWindowPadding},
        {"NoNavInputs",               ImGuiWindowFlags_NoNavInputs},
        {"NoNavFocus",                ImGuiWindowFlags_NoNavFocus},
        {"UnsavedDocument",           ImGuiWindowFlags_UnsavedDocument},
        {"NoDocking",                 ImGuiWindowFlags_NoDocking},
        {"NoNav",                     ImGuiWindowFlags_NoNav},
        {"NoDecoration",              ImGuiWindowFlags_NoDecoration},
        {"NoInputs",                  ImGuiWindowFlags_NoInputs},
        {"NavFlattened",              ImGuiWindowFlags_NavFlattened},
    });

    imgui.set_function("BeginPopup",
        sol::overload(
            [](const char* str_id) { return ImGui::BeginPopup(str_id); },
            sol::resolve<bool(const char*, ImGuiWindowFlags)>(ImGui::BeginPopup)));
    imgui.set_function("BeginPopupModal",
        sol::overload(
            [](const char* str_id) { return ImGui::BeginPopupModal(str_id); },
            [](const char* str_id, bool open) { auto ret = ImGui::BeginPopupModal(str_id, &open); return std::tuple{ret, open}; },
            [](const char* str_id, bool open, ImGuiWindowFlags flags) { auto ret = ImGui::BeginPopupModal(str_id, &open, flags); return std::tuple{ret, open}; }));
    imgui.set_function("EndPopup", sol::resolve<void()>(ImGui::EndPopup));
    imgui.set_function("OpenPopup",
        sol::overload(
            [](const char* str_id) { return ImGui::OpenPopup(str_id); },
            sol::resolve<void(const char*, ImGuiPopupFlags)>(ImGui::OpenPopup),
            [](ImGuiID id) { return ImGui::OpenPopup(id); },
            sol::resolve<void(ImGuiID, ImGuiPopupFlags)>(ImGui::OpenPopup)));
    imgui.set_function("OpenPopupOnItemClick",
        sol::overload(
            []() { return ImGui::OpenPopupOnItemClick(); },
            [](const char* str_id) { return ImGui::OpenPopupOnItemClick(str_id); },
            sol::resolve<void(const char*, ImGuiPopupFlags)>(ImGui::OpenPopupOnItemClick)));
    imgui.set_function("CloseCurrentPopup", sol::resolve<void()>(ImGui::CloseCurrentPopup));
    imgui.set_function("BeginPopupContextItem",
        sol::overload(
            []() { return ImGui::BeginPopupContextItem(); },
            [](const char* str_id) { return ImGui::BeginPopupContextItem(str_id); },
            sol::resolve<bool(const char*, ImGuiPopupFlags)>(ImGui::BeginPopupContextItem)));
    imgui.set_function("BeginPopupContextWindow",
        sol::overload(
            []() { return ImGui::BeginPopupContextWindow(); },
            [](const char* str_id) { return ImGui::BeginPopupContextWindow(str_id); },
            sol::resolve<bool(const char*, ImGuiPopupFlags)>(ImGui::BeginPopupContextWindow)));
    imgui.set_function("BeginPopupContextVoid",
        sol::overload(
            []() { return ImGui::BeginPopupContextVoid(); },
            [](const char* str_id) { return ImGui::BeginPopupContextVoid(str_id); },
            sol::resolve<bool(const char*, ImGuiPopupFlags)>(ImGui::BeginPopupContextVoid)));
    imgui.set_function("IsPopupOpen",
        sol::overload(
            [](const char* str_id) { return ImGui::IsPopupOpen(str_id); },
            sol::resolve<bool(const char*, ImGuiPopupFlags)>(ImGui::IsPopupOpen)));
}
