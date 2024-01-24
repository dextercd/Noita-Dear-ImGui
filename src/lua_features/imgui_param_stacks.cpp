#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_param_stacks(sol::table& imgui)
{
    imgui.new_enum<ImGuiCol_>("Col", {
        {"Text",                  ImGuiCol_Text},
        {"TextDisabled",          ImGuiCol_TextDisabled},
        {"WindowBg",              ImGuiCol_WindowBg},
        {"ChildBg",               ImGuiCol_ChildBg},
        {"PopupBg",               ImGuiCol_PopupBg},
        {"Border",                ImGuiCol_Border},
        {"BorderShadow",          ImGuiCol_BorderShadow},
        {"FrameBg",               ImGuiCol_FrameBg},
        {"FrameBgHovered",        ImGuiCol_FrameBgHovered},
        {"FrameBgActive",         ImGuiCol_FrameBgActive},
        {"TitleBg",               ImGuiCol_TitleBg},
        {"TitleBgActive",         ImGuiCol_TitleBgActive},
        {"TitleBgCollapsed",      ImGuiCol_TitleBgCollapsed},
        {"MenuBarBg",             ImGuiCol_MenuBarBg},
        {"ScrollbarBg",           ImGuiCol_ScrollbarBg},
        {"ScrollbarGrab",         ImGuiCol_ScrollbarGrab},
        {"ScrollbarGrabHovered",  ImGuiCol_ScrollbarGrabHovered},
        {"ScrollbarGrabActive",   ImGuiCol_ScrollbarGrabActive},
        {"CheckMark",             ImGuiCol_CheckMark},
        {"SliderGrab",            ImGuiCol_SliderGrab},
        {"SliderGrabActive",      ImGuiCol_SliderGrabActive},
        {"Button",                ImGuiCol_Button},
        {"ButtonHovered",         ImGuiCol_ButtonHovered},
        {"ButtonActive",          ImGuiCol_ButtonActive},
        {"Header",                ImGuiCol_Header},
        {"HeaderHovered",         ImGuiCol_HeaderHovered},
        {"HeaderActive",          ImGuiCol_HeaderActive},
        {"Separator",             ImGuiCol_Separator},
        {"SeparatorHovered",      ImGuiCol_SeparatorHovered},
        {"SeparatorActive",       ImGuiCol_SeparatorActive},
        {"ResizeGrip",            ImGuiCol_ResizeGrip},
        {"ResizeGripHovered",     ImGuiCol_ResizeGripHovered},
        {"ResizeGripActive",      ImGuiCol_ResizeGripActive},
        {"Tab",                   ImGuiCol_Tab},
        {"TabHovered",            ImGuiCol_TabHovered},
        {"TabActive",             ImGuiCol_TabActive},
        {"TabUnfocused",          ImGuiCol_TabUnfocused},
        {"TabUnfocusedActive",    ImGuiCol_TabUnfocusedActive},
        {"PlotLines",             ImGuiCol_PlotLines},
        {"PlotLinesHovered",      ImGuiCol_PlotLinesHovered},
        {"PlotHistogram",         ImGuiCol_PlotHistogram},
        {"PlotHistogramHovered",  ImGuiCol_PlotHistogramHovered},
        {"TableHeaderBg",         ImGuiCol_TableHeaderBg},
        {"TableBorderStrong",     ImGuiCol_TableBorderStrong},
        {"TableBorderLight",      ImGuiCol_TableBorderLight},
        {"TableRowBg",            ImGuiCol_TableRowBg},
        {"TableRowBgAlt",         ImGuiCol_TableRowBgAlt},
        {"TextSelectedBg",        ImGuiCol_TextSelectedBg},
        {"DragDropTarget",        ImGuiCol_DragDropTarget},
        {"NavHighlight",          ImGuiCol_NavHighlight},
        {"NavWindowingHighlight", ImGuiCol_NavWindowingHighlight},
        {"NavWindowingDimBg",     ImGuiCol_NavWindowingDimBg},
        {"ModalWindowDimBg",      ImGuiCol_ModalWindowDimBg},
        {"COUNT",                 ImGuiCol_COUNT},
    });

    imgui.new_enum<ImGuiStyleVar_>("StyleVar", {
        {"Alpha",                   ImGuiStyleVar_Alpha},
        {"DisabledAlpha",           ImGuiStyleVar_DisabledAlpha},
        {"WindowPadding",           ImGuiStyleVar_WindowPadding},
        {"WindowRounding",          ImGuiStyleVar_WindowRounding},
        {"WindowBorderSize",        ImGuiStyleVar_WindowBorderSize},
        {"WindowMinSize",           ImGuiStyleVar_WindowMinSize},
        {"WindowTitleAlign",        ImGuiStyleVar_WindowTitleAlign},
        {"ChildRounding",           ImGuiStyleVar_ChildRounding},
        {"ChildBorderSize",         ImGuiStyleVar_ChildBorderSize},
        {"PopupRounding",           ImGuiStyleVar_PopupRounding},
        {"PopupBorderSize",         ImGuiStyleVar_PopupBorderSize},
        {"FramePadding",            ImGuiStyleVar_FramePadding},
        {"FrameRounding",           ImGuiStyleVar_FrameRounding},
        {"FrameBorderSize",         ImGuiStyleVar_FrameBorderSize},
        {"ItemSpacing",             ImGuiStyleVar_ItemSpacing},
        {"ItemInnerSpacing",        ImGuiStyleVar_ItemInnerSpacing},
        {"IndentSpacing",           ImGuiStyleVar_IndentSpacing},
        {"CellPadding",             ImGuiStyleVar_CellPadding},
        {"ScrollbarSize",           ImGuiStyleVar_ScrollbarSize},
        {"ScrollbarRounding",       ImGuiStyleVar_ScrollbarRounding},
        {"GrabMinSize",             ImGuiStyleVar_GrabMinSize},
        {"GrabRounding",            ImGuiStyleVar_GrabRounding},
        {"TabRounding",             ImGuiStyleVar_TabRounding},
        {"TabBarBorderSize",        ImGuiStyleVar_TabBarBorderSize},
        {"ButtonTextAlign",         ImGuiStyleVar_ButtonTextAlign},
        {"SelectableTextAlign",     ImGuiStyleVar_SelectableTextAlign},
        {"SeparatorTextBorderSize", ImGuiStyleVar_SeparatorTextBorderSize},
        {"SeparatorTextAlign",      ImGuiStyleVar_SeparatorTextAlign},
        {"SeparatorTextPadding",    ImGuiStyleVar_SeparatorTextPadding},
        {"DockingSeparatorSize",    ImGuiStyleVar_DockingSeparatorSize},
        {"COUNT",                   ImGuiStyleVar_COUNT},
    });

    imgui.set_function("PushStyleColor",
        sol::overload(
            [](ImGuiCol idx, float r, float g, float b) -> void { ImGui::PushStyleColor(idx, ImVec4{r, g, b, 1.0f}); },
            [](ImGuiCol idx, float r, float g, float b, float a) { ImGui::PushStyleColor(idx, ImVec4{r, g, b, a}); }));

    imgui.set_function("PopStyleColor",
        sol::overload(
            []() { return ImGui::PopStyleColor(); },
            sol::resolve<void(int)>(ImGui::PopStyleColor)));

    imgui.set_function("PushStyleVar",
        sol::overload(
            sol::resolve<void(ImGuiStyleVar, float)>(ImGui::PushStyleVar),
            [](ImGuiStyleVar idx, float valx, float valy) { return ImGui::PushStyleVar(idx, {valx, valy}); }));

    imgui.set_function("PopStyleVar",
        sol::overload(
            []() { return ImGui::PopStyleVar(); },
            sol::resolve<void(int)>(ImGui::PopStyleVar)));

    imgui.set_function("PushButtonRepeat", sol::resolve<void(bool)>(ImGui::PushButtonRepeat));
    imgui.set_function("PopButtonRepeat", sol::resolve<void()>(ImGui::PopButtonRepeat));
    imgui.set_function("PushItemWidth", sol::resolve<void(float)>(ImGui::PushItemWidth));
    imgui.set_function("PopItemWidth", sol::resolve<void()>(ImGui::PopItemWidth));
    imgui.set_function("SetNextItemWidth", sol::resolve<void(float)>(ImGui::SetNextItemWidth));
    imgui.set_function("CalcItemWidth", sol::resolve<float()>(ImGui::CalcItemWidth));
    imgui.set_function("PushTextWrapPos",
        sol::overload(
            []() { return ImGui::PushTextWrapPos(); },
            sol::resolve<void(float)>(ImGui::PushTextWrapPos)));
    imgui.set_function("PopTextWrapPos", sol::resolve<void()>(ImGui::PopTextWrapPos));
}
