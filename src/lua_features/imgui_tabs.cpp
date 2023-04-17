#include <tuple>
#include <optional>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_tabs(sol::table& imgui)
{
    imgui.new_enum("TabBarFlags",
        "None",                         ImGuiTabBarFlags_None,
        "Reorderable",                  ImGuiTabBarFlags_Reorderable,
        "AutoSelectNewTabs",            ImGuiTabBarFlags_AutoSelectNewTabs,
        "TabListPopupButton",           ImGuiTabBarFlags_TabListPopupButton,
        "NoCloseWithMiddleMouseButton", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton,
        "NoTabListScrollingButtons",    ImGuiTabBarFlags_NoTabListScrollingButtons,
        "NoTooltip",                    ImGuiTabBarFlags_NoTooltip,
        "FittingPolicyResizeDown",      ImGuiTabBarFlags_FittingPolicyResizeDown,
        "FittingPolicyScroll",          ImGuiTabBarFlags_FittingPolicyScroll,
        "FittingPolicyMask_",           ImGuiTabBarFlags_FittingPolicyMask_,
        "FittingPolicyDefault_",        ImGuiTabBarFlags_FittingPolicyDefault_
    );

    imgui.set_function("BeginTabBar",
        sol::overload(
            [](const char* str_id) { return ImGui::BeginTabBar(str_id); },
            sol::resolve<bool(const char*, ImGuiTabBarFlags)>(ImGui::BeginTabBar)));

    imgui.set_function("EndTabBar", sol::resolve<void()>(ImGui::EndTabBar));

    imgui.new_enum("TabItemFlags",
        "None",                         ImGuiTabItemFlags_None,
        "UnsavedDocument",              ImGuiTabItemFlags_UnsavedDocument,
        "SetSelected",                  ImGuiTabItemFlags_SetSelected,
        "NoCloseWithMiddleMouseButton", ImGuiTabItemFlags_NoCloseWithMiddleMouseButton,
        "NoPushId",                     ImGuiTabItemFlags_NoPushId,
        "NoTooltip",                    ImGuiTabItemFlags_NoTooltip,
        "NoReorder",                    ImGuiTabItemFlags_NoReorder,
        "Leading",                      ImGuiTabItemFlags_Leading,
        "Trailing",                     ImGuiTabItemFlags_Trailing
    );

    imgui.set_function("BeginTabItem",
        [](
            sol::this_state s,
            const char* label,
            std::optional<bool> open,
            std::optional<ImGuiTabItemFlags> flags
        ) -> std::tuple<bool, std::optional<bool>> {
            sol::state_view lua{s};

            bool* p_open = nullptr;
            if (open.has_value())
                p_open = &open.value();

            auto ret = ImGui::BeginTabItem(label, p_open, flags.value_or(0));

            if (p_open)
                return std::tuple{ret, *p_open};

            return std::tuple{ret, std::nullopt};
        }
    );

    imgui.set_function("EndTabItem", sol::resolve<void()>(ImGui::EndTabItem));

    imgui.set_function("TabItemButton",
        sol::overload(
            [](const char* label) { return ImGui::TabItemButton(label); },
            sol::resolve<bool(const char*, ImGuiTabItemFlags)>(ImGui::TabItemButton)));

    imgui.set_function("SetTabItemClosed", sol::resolve<void(const char*)>(ImGui::SetTabItemClosed));
}
