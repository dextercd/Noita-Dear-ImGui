#include <array>
#include <optional>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_style(sol::table& imgui)
{
    imgui.new_enum("Dir",
        "None", ImGuiDir_None,
        "Left", ImGuiDir_Left,
        "Right", ImGuiDir_Right,
        "Up", ImGuiDir_Up,
        "Down", ImGuiDir_Down,
        "COUNT", ImGuiDir_COUNT
    );

    auto style_type = imgui.new_usertype<ImGuiStyle>("Style", sol::no_constructor,
        "Alpha", sol::readonly(&ImGuiStyle::Alpha),
        "DisabledAlpha", sol::readonly(&ImGuiStyle::DisabledAlpha),
        "WindowPadding_x", sol::property([](const ImGuiStyle& style) { return style.WindowPadding.x; }),
        "WindowPadding_y", sol::property([](const ImGuiStyle& style) { return style.WindowPadding.y; }),
        "WindowRounding", sol::readonly(&ImGuiStyle::WindowRounding),
        "WindowBorderSize", sol::readonly(&ImGuiStyle::WindowBorderSize),
        "WindowMinSize_x", sol::property([](const ImGuiStyle& style) { return style.WindowMinSize.x; }),
        "WindowMinSize_y", sol::property([](const ImGuiStyle& style) { return style.WindowMinSize.y; }),
        "WindowTitleAlign_x", sol::property([](const ImGuiStyle& style) { return style.WindowTitleAlign.x; }),
        "WindowTitleAlign_y", sol::property([](const ImGuiStyle& style) { return style.WindowTitleAlign.y; }),
        "WindowMenuButtonPosition", sol::readonly(&ImGuiStyle::WindowMenuButtonPosition),
        "ChildRounding", sol::readonly(&ImGuiStyle::ChildRounding),
        "ChildBorderSize", sol::readonly(&ImGuiStyle::ChildBorderSize),
        "PopupRounding", sol::readonly(&ImGuiStyle::PopupRounding),
        "PopupBorderSize", sol::readonly(&ImGuiStyle::PopupBorderSize),
        "FramePadding_x", sol::property([](const ImGuiStyle& style) { return style.FramePadding.x; }),
        "FramePadding_y", sol::property([](const ImGuiStyle& style) { return style.FramePadding.y; }),
        "FrameRounding", sol::readonly(&ImGuiStyle::FrameRounding),
        "FrameBorderSize", sol::readonly(&ImGuiStyle::FrameBorderSize),
        "ItemSpacing_x", sol::property([](const ImGuiStyle& style) { return style.ItemSpacing.x; }),
        "ItemSpacing_y", sol::property([](const ImGuiStyle& style) { return style.ItemSpacing.y; }),
        "ItemInnerSpacing_x", sol::property([](const ImGuiStyle& style) { return style.ItemInnerSpacing.x; }),
        "ItemInnerSpacing_y", sol::property([](const ImGuiStyle& style) { return style.ItemInnerSpacing.y; }),
        "CellPadding_x", sol::property([](const ImGuiStyle& style) { return style.CellPadding.x; }),
        "CellPadding_y", sol::property([](const ImGuiStyle& style) { return style.CellPadding.y; }),
        "TouchExtraPadding_x", sol::property([](const ImGuiStyle& style) { return style.TouchExtraPadding.x; }),
        "TouchExtraPadding_y", sol::property([](const ImGuiStyle& style) { return style.TouchExtraPadding.y; }),
        "IndentSpacing", sol::readonly(&ImGuiStyle::IndentSpacing),
        "ColumnsMinSpacing", sol::readonly(&ImGuiStyle::ColumnsMinSpacing),
        "ScrollbarSize", sol::readonly(&ImGuiStyle::ScrollbarSize),
        "ScrollbarRounding", sol::readonly(&ImGuiStyle::ScrollbarRounding),
        "GrabMinSize", sol::readonly(&ImGuiStyle::GrabMinSize),
        "GrabRounding", sol::readonly(&ImGuiStyle::GrabRounding),
        "LogSliderDeadzone", sol::readonly(&ImGuiStyle::LogSliderDeadzone),
        "TabRounding", sol::readonly(&ImGuiStyle::TabRounding),
        "TabBorderSize", sol::readonly(&ImGuiStyle::TabBorderSize),
        "TabMinWidthForCloseButton", sol::readonly(&ImGuiStyle::TabMinWidthForCloseButton),
        "TabBarBorderSize", sol::readonly(&ImGuiStyle::TabBarBorderSize),
        "TabBarOverlineSize", sol::readonly(&ImGuiStyle::TabBarOverlineSize),
        "TableAngledHeadersAngle", sol::readonly(&ImGuiStyle::TableAngledHeadersAngle),
        "TableAngledHeadersTextAlign_x", sol::property([](const ImGuiStyle& style) { return style.TableAngledHeadersTextAlign.x; }),
        "TableAngledHeadersTextAlign_y", sol::property([](const ImGuiStyle& style) { return style.TableAngledHeadersTextAlign.y; }),
        "ColorButtonPosition", sol::readonly(&ImGuiStyle::ColorButtonPosition),
        "ButtonTextAlign_x", sol::property([](const ImGuiStyle& style) { return style.ButtonTextAlign.x; }),
        "ButtonTextAlign_y", sol::property([](const ImGuiStyle& style) { return style.ButtonTextAlign.y; }),
        "SelectableTextAlign_x", sol::property([](const ImGuiStyle& style) { return style.SelectableTextAlign.x; }),
        "SelectableTextAlign_y", sol::property([](const ImGuiStyle& style) { return style.SelectableTextAlign.y; }),
        "SeparatorTextBorderSize", sol::readonly(&ImGuiStyle::SeparatorTextBorderSize),
        "SeparatorTextAlign_x", sol::property([](const ImGuiStyle& style) { return style.SeparatorTextAlign.x; }),
        "SeparatorTextAlign_y", sol::property([](const ImGuiStyle& style) { return style.SeparatorTextAlign.y; }),
        "SeparatorTextPadding_x", sol::property([](const ImGuiStyle& style) { return style.SeparatorTextPadding.x; }),
        "SeparatorTextPadding_y", sol::property([](const ImGuiStyle& style) { return style.SeparatorTextPadding.y; }),
        "DisplayWindowPadding_x", sol::property([](const ImGuiStyle& style) { return style.DisplayWindowPadding.x; }),
        "DisplayWindowPadding_y", sol::property([](const ImGuiStyle& style) { return style.DisplayWindowPadding.y; }),
        "DisplaySafeAreaPadding_x", sol::property([](const ImGuiStyle& style) { return style.DisplaySafeAreaPadding.x; }),
        "DisplaySafeAreaPadding_y", sol::property([](const ImGuiStyle& style) { return style.DisplaySafeAreaPadding.y; }),
        "DockingSeparatorSize", sol::readonly(&ImGuiStyle::DockingSeparatorSize),
        "MouseCursorScale", sol::readonly(&ImGuiStyle::MouseCursorScale),
        "AntiAliasedLines", sol::readonly(&ImGuiStyle::AntiAliasedLines),
        "AntiAliasedLinesUseTex", sol::readonly(&ImGuiStyle::AntiAliasedLinesUseTex),
        "AntiAliasedFill", sol::readonly(&ImGuiStyle::AntiAliasedFill),
        "CurveTessellationTol", sol::readonly(&ImGuiStyle::CurveTessellationTol),
        "CircleTessellationMaxError", sol::readonly(&ImGuiStyle::CircleTessellationMaxError),
        "Color", [](const ImGuiStyle& style, int index) -> std::optional<std::tuple<float, float, float, float>>{
            if (index < 0 || index >= ImGuiCol_COUNT)
                return std::nullopt;

            auto c = style.Colors[index];
            return std::tuple{c.x, c.y, c.z, c.w};
        }
    );

    // Only return a copy for now
    imgui.set_function("GetStyle", []() -> ImGuiStyle { return ImGui::GetStyle(); });

}
