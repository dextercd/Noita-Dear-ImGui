#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_tables(sol::table& imgui)
{
    imgui.new_enum<ImGuiTableFlags_>("TableFlags", {
        {"None",                       ImGuiTableFlags_None},
        {"Resizable",                  ImGuiTableFlags_Resizable},
        {"Reorderable",                ImGuiTableFlags_Reorderable},
        {"Hideable",                   ImGuiTableFlags_Hideable},
        {"Sortable",                   ImGuiTableFlags_Sortable},
        {"NoSavedSettings",            ImGuiTableFlags_NoSavedSettings},
        {"ContextMenuInBody",          ImGuiTableFlags_ContextMenuInBody},
        {"RowBg",                      ImGuiTableFlags_RowBg},
        {"BordersInnerH",              ImGuiTableFlags_BordersInnerH},
        {"BordersOuterH",              ImGuiTableFlags_BordersOuterH},
        {"BordersInnerV",              ImGuiTableFlags_BordersInnerV},
        {"BordersOuterV",              ImGuiTableFlags_BordersOuterV},
        {"BordersH",                   ImGuiTableFlags_BordersH},
        {"BordersV",                   ImGuiTableFlags_BordersV},
        {"BordersInner",               ImGuiTableFlags_BordersInner},
        {"BordersOuter",               ImGuiTableFlags_BordersOuter},
        {"Borders",                    ImGuiTableFlags_Borders},
        {"NoBordersInBody",            ImGuiTableFlags_NoBordersInBody},
        {"NoBordersInBodyUntilResize", ImGuiTableFlags_NoBordersInBodyUntilResize},
        {"SizingFixedFit",             ImGuiTableFlags_SizingFixedFit},
        {"SizingFixedSame",            ImGuiTableFlags_SizingFixedSame},
        {"SizingStretchProp",          ImGuiTableFlags_SizingStretchProp},
        {"SizingStretchSame",          ImGuiTableFlags_SizingStretchSame},
        {"NoHostExtendX",              ImGuiTableFlags_NoHostExtendX},
        {"NoHostExtendY",              ImGuiTableFlags_NoHostExtendY},
        {"NoKeepColumnsVisible",       ImGuiTableFlags_NoKeepColumnsVisible},
        {"PreciseWidths",              ImGuiTableFlags_PreciseWidths},
        {"NoClip",                     ImGuiTableFlags_NoClip},
        {"PadOuterX",                  ImGuiTableFlags_PadOuterX},
        {"NoPadOuterX",                ImGuiTableFlags_NoPadOuterX},
        {"NoPadInnerX",                ImGuiTableFlags_NoPadInnerX},
        {"ScrollX",                    ImGuiTableFlags_ScrollX},
        {"ScrollY",                    ImGuiTableFlags_ScrollY},
        {"SortMulti",                  ImGuiTableFlags_SortMulti},
        {"SortTristate",               ImGuiTableFlags_SortTristate},
    });

    imgui.new_enum<ImGuiTableRowFlags_>("TableRowFlags", {
        {"None",    ImGuiTableRowFlags_None},
        {"Headers", ImGuiTableRowFlags_Headers},
    });

    imgui.new_enum<ImGuiTableColumnFlags_>("TableColumnFlags", {
        {"None",                 ImGuiTableColumnFlags_None},
        {"Disabled",             ImGuiTableColumnFlags_Disabled},
        {"DefaultHide",          ImGuiTableColumnFlags_DefaultHide},
        {"DefaultSort",          ImGuiTableColumnFlags_DefaultSort},
        {"WidthStretch",         ImGuiTableColumnFlags_WidthStretch},
        {"WidthFixed",           ImGuiTableColumnFlags_WidthFixed},
        {"NoResize",             ImGuiTableColumnFlags_NoResize},
        {"NoReorder",            ImGuiTableColumnFlags_NoReorder},
        {"NoHide",               ImGuiTableColumnFlags_NoHide},
        {"NoClip",               ImGuiTableColumnFlags_NoClip},
        {"NoSort",               ImGuiTableColumnFlags_NoSort},
        {"NoSortAscending",      ImGuiTableColumnFlags_NoSortAscending},
        {"NoSortDescending",     ImGuiTableColumnFlags_NoSortDescending},
        {"NoHeaderLabel",        ImGuiTableColumnFlags_NoHeaderLabel},
        {"NoHeaderWidth",        ImGuiTableColumnFlags_NoHeaderWidth},
        {"PreferSortAscending",  ImGuiTableColumnFlags_PreferSortAscending},
        {"PreferSortDescending", ImGuiTableColumnFlags_PreferSortDescending},
        {"IndentEnable",         ImGuiTableColumnFlags_IndentEnable},
        {"IndentDisable",        ImGuiTableColumnFlags_IndentDisable},
        {"IsEnabled",            ImGuiTableColumnFlags_IsEnabled},
        {"IsVisible",            ImGuiTableColumnFlags_IsVisible},
        {"IsSorted",             ImGuiTableColumnFlags_IsSorted},
        {"IsHovered",            ImGuiTableColumnFlags_IsHovered},
    });

    imgui.new_enum<ImGuiTableBgTarget_>("TableBgTarget", {
        {"None",   ImGuiTableBgTarget_None},
        {"RowBg0", ImGuiTableBgTarget_RowBg0},
        {"RowBg1", ImGuiTableBgTarget_RowBg1},
        {"CellBg", ImGuiTableBgTarget_CellBg},
    });

    imgui.set_function("BeginTable",
        sol::overload(
            [](const char* str_id, int column) { return ImGui::BeginTable(str_id, column); },
            [](const char* str_id, int column, ImGuiTableFlags flags) { return ImGui::BeginTable(str_id, column, flags); },
            [](const char* str_id, int column, ImGuiTableFlags flags, float outer_size_x, float outer_size_y) { return ImGui::BeginTable(str_id, column, flags, {outer_size_x, outer_size_y}); },
            [](const char* str_id, int column, ImGuiTableFlags flags, float outer_size_x, float outer_size_y, float inner_size) { return ImGui::BeginTable(str_id, column, flags, {outer_size_x, outer_size_y}, inner_size); }));
    imgui.set_function("EndTable", sol::resolve<void()>(ImGui::EndTable));
    imgui.set_function("TableNextRow",
        sol::overload(
            []() { return ImGui::TableNextRow(); },
            [](ImGuiTableRowFlags row_flags) { return ImGui::TableNextRow(row_flags); },
            sol::resolve<void(ImGuiTableRowFlags, float)>(ImGui::TableNextRow)));
    imgui.set_function("TableNextColumn", sol::resolve<bool()>(ImGui::TableNextColumn));
    imgui.set_function("TableSetColumnIndex", sol::resolve<bool(int)>(ImGui::TableSetColumnIndex));
    imgui.set_function("TableSetupColumn",
        sol::overload(
            [](const char* label) { return ImGui::TableSetupColumn(label); },
            [](const char* label, ImGuiTableColumnFlags flags) { return ImGui::TableSetupColumn(label, flags); },
            [](const char* label, ImGuiTableColumnFlags flags, float init_width_or_weight) { return ImGui::TableSetupColumn(label, flags, init_width_or_weight); },
            sol::resolve<void(const char*, ImGuiTableColumnFlags, float, ImGuiID)>(ImGui::TableSetupColumn)));
    imgui.set_function("TableSetupScrollFreeze", sol::resolve<void(int, int)>(ImGui::TableSetupScrollFreeze));
    imgui.set_function("TableHeadersRow", sol::resolve<void()>(ImGui::TableHeadersRow));
    imgui.set_function("TableHeader", sol::resolve<void(const char* label)>(ImGui::TableHeader));
    // IMGUI_API ImGuiTableSortSpecs*  TableGetSortSpecs();
    imgui.set_function("TableGetColumnCount", sol::resolve<int()>(ImGui::TableGetColumnCount));
    imgui.set_function("TableGetColumnIndex", sol::resolve<int()>(ImGui::TableGetColumnIndex));
    imgui.set_function("TableGetRowIndex", sol::resolve<int()>(ImGui::TableGetRowIndex));
    imgui.set_function("TableGetColumnName",
        sol::overload(
            []() { return ImGui::TableGetColumnName(); },
            sol::resolve<const char*(int)>(ImGui::TableGetColumnName)));
    imgui.set_function("TableGetColumnFlags",
        sol::overload(
            []() { return ImGui::TableGetColumnFlags(); },
            sol::resolve<ImGuiTableColumnFlags(int)>(ImGui::TableGetColumnFlags)));
    imgui.set_function("TableSetColumnEnabled", sol::resolve<void(int, bool)>(ImGui::TableSetColumnEnabled));
    imgui.set_function("TableSetBgColor",
        sol::overload(
            [](ImGuiTableBgTarget target, float r, float g, float b, float a) { return ImGui::TableSetBgColor(target, ImGui::GetColorU32(ImVec4{r, g, b, a})); },
            [](ImGuiTableBgTarget target, float r, float g, float b, float a, int column_n) { return ImGui::TableSetBgColor(target, ImGui::GetColorU32(ImVec4{r, g, b, a}), column_n); }));
}
