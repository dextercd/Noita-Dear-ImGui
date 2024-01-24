#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_widget_utils(sol::table& imgui)
{
    imgui.new_enum("HoveredFlags",
        "None",                         ImGuiHoveredFlags_None,
        "ChildWindows",                 ImGuiHoveredFlags_ChildWindows,
        "RootWindow",                   ImGuiHoveredFlags_RootWindow,
        "AnyWindow",                    ImGuiHoveredFlags_AnyWindow,
        "NoPopupHierarchy",             ImGuiHoveredFlags_NoPopupHierarchy,
        "DockHierarchy",                ImGuiHoveredFlags_DockHierarchy,
        "AllowWhenBlockedByPopup",      ImGuiHoveredFlags_AllowWhenBlockedByPopup,
        // "AllowWhenBlockedByModal",   ImGuiHoveredFlags_AllowWhenBlockedByModal,
        "AllowWhenBlockedByActiveItem", ImGuiHoveredFlags_AllowWhenBlockedByActiveItem,
        "AllowWhenOverlappedByItem",    ImGuiHoveredFlags_AllowWhenOverlappedByItem,
        "AllowWhenOverlappedByWindow",  ImGuiHoveredFlags_AllowWhenOverlappedByWindow,
        "AllowWhenDisabled",            ImGuiHoveredFlags_AllowWhenDisabled,
        "NoNavOverride",                ImGuiHoveredFlags_NoNavOverride,
        "AllowWhenOverlapped",          ImGuiHoveredFlags_AllowWhenOverlapped,
        "RectOnly",                     ImGuiHoveredFlags_RectOnly,
        "RootAndChildWindows",          ImGuiHoveredFlags_RootAndChildWindows,
        "ForTooltip",                   ImGuiHoveredFlags_ForTooltip,
        "Stationary",                   ImGuiHoveredFlags_Stationary,
        "DelayNone",                    ImGuiHoveredFlags_DelayNone,
        "DelayShort",                   ImGuiHoveredFlags_DelayShort,
        "DelayNormal",                  ImGuiHoveredFlags_DelayNormal,
        "NoSharedDelay",                ImGuiHoveredFlags_NoSharedDelay
    );

    imgui.set_function("IsItemHovered",
        sol::overload(
            []() { return ImGui::IsItemHovered(); },
            sol::resolve<bool(ImGuiHoveredFlags)>(ImGui::IsItemHovered)));
    imgui.set_function("IsItemActive", sol::resolve<bool()>(ImGui::IsItemActive));
    imgui.set_function("IsItemFocused", sol::resolve<bool()>(ImGui::IsItemFocused));
    imgui.set_function("IsItemClicked",
        sol::overload(
            []() { return ImGui::IsItemClicked(); },
            sol::resolve<bool(ImGuiMouseButton)>(ImGui::IsItemClicked)));
    imgui.set_function("IsItemVisible", sol::resolve<bool()>(ImGui::IsItemVisible));
    imgui.set_function("IsItemEdited", sol::resolve<bool()>(ImGui::IsItemEdited));
    imgui.set_function("IsItemActivated", sol::resolve<bool()>(ImGui::IsItemActivated));
    imgui.set_function("IsItemDeactivated", sol::resolve<bool()>(ImGui::IsItemDeactivated));
    imgui.set_function("IsItemDeactivatedAfterEdit", sol::resolve<bool()>(ImGui::IsItemDeactivatedAfterEdit));
    imgui.set_function("IsItemToggledOpen", sol::resolve<bool()>(ImGui::IsItemToggledOpen));
    imgui.set_function("IsAnyItemHovered", sol::resolve<bool()>(ImGui::IsAnyItemHovered));
    imgui.set_function("IsAnyItemActive", sol::resolve<bool()>(ImGui::IsAnyItemActive));
    imgui.set_function("IsAnyItemFocused", sol::resolve<bool()>(ImGui::IsAnyItemFocused));
    imgui.set_function("GetItemID", sol::resolve<ImGuiID()>(ImGui::GetItemID));
    imgui.set_function("GetItemRectMin", []() -> std::tuple<float, float> { auto ret = ImGui::GetItemRectMin(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("GetItemRectMax", []() -> std::tuple<float, float> { auto ret = ImGui::GetItemRectMax(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("GetItemRectSize", []() -> std::tuple<float, float> { auto ret = ImGui::GetItemRectSize(); return std::tuple{ret.x, ret.y}; });
    imgui.set_function("SetNextItemAllowOverlap", sol::resolve<void()>(ImGui::SetNextItemAllowOverlap));
}
