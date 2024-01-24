#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_trees(sol::table& imgui)
{
    imgui.new_enum("TreeNodeFlags",
        "None",                 ImGuiTreeNodeFlags_None,
        "Selected",             ImGuiTreeNodeFlags_Selected,
        "Framed",               ImGuiTreeNodeFlags_Framed,
        "AllowOverlap",         ImGuiTreeNodeFlags_AllowOverlap,
        "NoTreePushOnOpen",     ImGuiTreeNodeFlags_NoTreePushOnOpen,
        "NoAutoOpenOnLog",      ImGuiTreeNodeFlags_NoAutoOpenOnLog,
        "DefaultOpen",          ImGuiTreeNodeFlags_DefaultOpen,
        "OpenOnDoubleClick",    ImGuiTreeNodeFlags_OpenOnDoubleClick,
        "OpenOnArrow",          ImGuiTreeNodeFlags_OpenOnArrow,
        "Leaf",                 ImGuiTreeNodeFlags_Leaf,
        "Bullet",               ImGuiTreeNodeFlags_Bullet,
        "FramePadding",         ImGuiTreeNodeFlags_FramePadding,
        "SpanAvailWidth",       ImGuiTreeNodeFlags_SpanAvailWidth,
        "SpanFullWidth",        ImGuiTreeNodeFlags_SpanFullWidth,
        "SpanAllColumns",       ImGuiTreeNodeFlags_SpanAllColumns,
        "NavLeftJumpsBackHere", ImGuiTreeNodeFlags_NavLeftJumpsBackHere,
        //"NoScrollOnOpen",     ImGuiTreeNodeFlags_NoScrollOnOpen,
        "CollapsingHeader",     ImGuiTreeNodeFlags_CollapsingHeader
    );

    imgui.set_function("TreeNode",
        sol::overload(
            [](const char* label) { return ImGui::TreeNodeEx(label); },
            sol::resolve<bool(const char*, ImGuiTreeNodeFlags)>(ImGui::TreeNodeEx),
            [](const char* label, ImGuiTreeNodeFlags flags, const char* text) { return ImGui::TreeNodeEx(label, flags, "%s", text); }));
    imgui.set_function("TreePush", sol::resolve<void(const char*)>(ImGui::TreePush));
    imgui.set_function("TreePop", sol::resolve<void()>(ImGui::TreePop));
    imgui.set_function("GetTreeNodeToLabelSpacing", sol::resolve<float()>(ImGui::GetTreeNodeToLabelSpacing));

    imgui.set_function("CollapsingHeader",
        sol::overload(
            [](const char* label) -> bool { return ImGui::CollapsingHeader(label); },
            [](const char* label, ImGuiTreeNodeFlags flags) { return ImGui::CollapsingHeader(label, flags); },
            [](const char* label, bool visible) { auto ret = ImGui::CollapsingHeader(label, &visible); return std::tuple{ret, visible}; },
            [](const char* label, bool visible, ImGuiTreeNodeFlags flags) { auto ret = ImGui::CollapsingHeader(label, &visible, flags); return std::tuple{ret, visible}; }
        ));

    imgui.set_function("SetNextItemOpen",
        sol::overload(
            [](bool is_open) { return ImGui::SetNextItemOpen(is_open); },
            sol::resolve<void(bool, ImGuiCond)>(ImGui::SetNextItemOpen)));
}
