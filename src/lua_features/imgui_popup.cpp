#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

#include <noita_imgui/pause.hpp>

void add_imgui_popup(sol::table& imgui)
{
    imgui.new_enum<ImGuiPopupFlags>("PopupFlags", {
        {"None",                    ImGuiPopupFlags_None},
        {"MouseButtonLeft",         ImGuiPopupFlags_MouseButtonLeft},
        {"MouseButtonRight",        ImGuiPopupFlags_MouseButtonRight},
        {"MouseButtonMiddle",       ImGuiPopupFlags_MouseButtonMiddle},
        {"MouseButtonMask_",        ImGuiPopupFlags_MouseButtonMask_},
        {"MouseButtonDefault_",     ImGuiPopupFlags_MouseButtonDefault_},
        {"NoReopen",                ImGuiPopupFlags_NoReopen},
        {"NoOpenOverExistingPopup", ImGuiPopupFlags_NoOpenOverExistingPopup},
        {"NoOpenOverItems",         ImGuiPopupFlags_NoOpenOverItems},
        {"AnyPopupId",              ImGuiPopupFlags_AnyPopupId},
        {"AnyPopupLevel",           ImGuiPopupFlags_AnyPopupLevel},
        {"AnyPopup",                ImGuiPopupFlags_AnyPopup},
    });

    imgui.set_function("BeginPopup",
        sol::overload(
            [](const char* str_id) { return ImGui::BeginPopup(str_id); },
            sol::resolve<bool(const char*, ImGuiWindowFlags)>(ImGui::BeginPopup)));
    imgui.set_function("BeginPopupModal",
        sol::overload(
            [](const char* str_id) -> bool { return ImGui::BeginPopupModal(str_id); },
            [](const char* str_id, bool open) { auto ret = ImGui::BeginPopupModal(str_id, &open); return std::tuple{ret, open}; },
            [](const char* str_id, bool open, ImGuiWindowFlags flags) {
                if (just_unpaused)
                    flags |= ImGuiWindowFlags_NoFocusOnAppearing;
                auto ret = ImGui::BeginPopupModal(str_id, &open, flags);
                return std::tuple{ret, open};
            }));
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
