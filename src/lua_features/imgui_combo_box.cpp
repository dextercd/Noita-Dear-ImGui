#include <string>
#include <iostream>
#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

std::tuple<bool, int> ImGui_Combo(
    const char* label, int current_item, sol::table items,
    int popup_max_height_in_items = -1)
{
    const int expected_size = items.size();

    std::vector<std::string> storage;
    storage.reserve(expected_size);

    for (int i = 1; i <= expected_size; ++i) {
        std::string item_storage = items[i];
        storage.push_back(std::move(item_storage));
    }

    std::vector<const char*> combo_items(storage.size());
    std::transform(std::begin(storage), std::end(storage), std::begin(combo_items),
        [](const std::string& str) { return str.data(); });

    current_item -= 1; // Zero vs. one based indexing
    auto ret = ImGui::Combo(
        label, &current_item, combo_items.data(), combo_items.size(),
        popup_max_height_in_items);

    return {ret, current_item + 1};
}

void add_imgui_combo_box(sol::table& imgui)
{
    imgui.new_enum("ComboFlags",
        "None",           ImGuiComboFlags_None,
        "PopupAlignLeft", ImGuiComboFlags_PopupAlignLeft,
        "HeightSmall",    ImGuiComboFlags_HeightSmall,
        "HeightRegular",  ImGuiComboFlags_HeightRegular,
        "HeightLarge",    ImGuiComboFlags_HeightLarge,
        "HeightLargest",  ImGuiComboFlags_HeightLargest,
        "NoArrowButton",  ImGuiComboFlags_NoArrowButton,
        "NoPreview",      ImGuiComboFlags_NoPreview,
        "HeightMask_",    ImGuiComboFlags_HeightMask_
    );

    imgui.set_function("BeginCombo",
        sol::overload(
            [](const char* label, const char* preview_value) { return ImGui::BeginCombo(label, preview_value); },
            sol::resolve<bool(const char*, const char*, ImGuiComboFlags)>(ImGui::BeginCombo)));

    imgui.set_function("EndCombo", ImGui::EndCombo);

    imgui.set_function("Combo",
        sol::overload(
            [](const char* label, int current_item, sol::table items) { return ImGui_Combo(label, current_item, items); },
            [](const char* label, int current_item, sol::table items, int popup_max_height_in_items) { return ImGui_Combo(label, current_item, items, popup_max_height_in_items); }));
}
