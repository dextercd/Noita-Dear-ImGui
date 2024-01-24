#include <optional>
#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>
#include <imgui_internal.h>

void add_imgui_docking(sol::table& imgui)
{
    imgui.new_enum("DockNodeFlags",
        "None", ImGuiDockNodeFlags_None,
        "KeepAliveOnly", ImGuiDockNodeFlags_KeepAliveOnly,
        // "NoCentralNode", ImGuiDockNodeFlags_NoCentralNode,
        "NoDockingOverCentralNode", ImGuiDockNodeFlags_NoDockingOverCentralNode,
        "PassthruCentralNode", ImGuiDockNodeFlags_PassthruCentralNode,
        "NoDockingSplit", ImGuiDockNodeFlags_NoDockingSplit,
        "NoResize", ImGuiDockNodeFlags_NoResize,
        "AutoHideTabBar", ImGuiDockNodeFlags_AutoHideTabBar,
        "NoUndocking", ImGuiDockNodeFlags_NoUndocking
    );

    imgui.set_function("GetWindowDockID", []() { return ImGui::GetWindowDockID(); });

    imgui.set_function("SetNextWindowDockID",
        [](ImGuiID dock_id, std::optional<ImGuiCond> cond) {
            return ImGui::SetNextWindowDockID(dock_id, cond.value_or(0));
        }
    );

    imgui.set_function("DockBuilderDockWindow", [](const char* window_name, ImGuiID node_id) {
        return ImGui::DockBuilderDockWindow(window_name, node_id);
    });

    imgui.set_function("DockBuilderAddNode", [](
            std::optional<ImGuiID> node_id,
            std::optional<ImGuiDockNodeFlags> flags)
    {
        return ImGui::DockBuilderAddNode(node_id.value_or(0), flags.value_or(0));
    });

    imgui.set_function("DockBuilderRemoveNode", [](ImGuiID node_id) {
        return ImGui::DockBuilderRemoveNode(node_id);
    });

    imgui.set_function("DockBuilderRemoveNodeDockedWindows", [](
            ImGuiID node_id,
            std::optional<bool> clear_settings_ref)
    {
        return ImGui::DockBuilderRemoveNodeDockedWindows(node_id, clear_settings_ref.value_or(true));
    });

    imgui.set_function("DockBuilderRemoveNodeChildNodes", [](ImGuiID node_id) {
        return ImGui::DockBuilderRemoveNodeChildNodes(node_id);
    });

    imgui.set_function("DockBuilderSetNodePos", [](ImGuiID node_id, float x, float y) {
        return ImGui::DockBuilderSetNodePos(node_id, {x, y});
    });

    imgui.set_function("DockBuilderSetNodeSize", [](ImGuiID node_id, float width, float height) {
        return ImGui::DockBuilderSetNodeSize(node_id, {width, height});
    });

    imgui.set_function("DockBuilderSplitNode", [](
            ImGuiID node_id,
            ImGuiDir split_dir,
            float size_ratio_for_node_at_dir)
    {
        ImGuiID out_opposite_dir{};
        auto out_dir = ImGui::DockBuilderSplitNode(
                node_id, split_dir, size_ratio_for_node_at_dir, nullptr, &out_opposite_dir);
        return std::tuple{out_dir, out_opposite_dir};
    });

    imgui.set_function("DockBuilderCopyWindowSettings", [](const char* src_name, const char* dst_name) {
        return ImGui::DockBuilderCopyWindowSettings(src_name, dst_name);
    });

    imgui.set_function("DockBuilderFinish", [](ImGuiID node_id) {
        return ImGui::DockBuilderFinish(node_id);
    });
}
