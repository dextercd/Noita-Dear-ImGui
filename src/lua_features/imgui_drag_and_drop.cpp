#include <sol/sol.hpp>
#include <imgui.h>

using drag_drop_identifier = unsigned int;

bool SetDragDropPayload(sol::this_state s, const char* type, sol::object payload, ImGuiCond cond = 0)
{
    static drag_drop_identifier drag_drop_id = 0;

    sol::state_view lua{s};
    auto globals = lua.globals();

    bool ret = ImGui::SetDragDropPayload(type, &drag_drop_id, sizeof(drag_drop_id), cond);
    if (ret) {
        globals["__imgui_drag_drop_id"] = drag_drop_id++;
        globals["__imgui_drag_drop_value"] = payload;
    }

    return ret;
}

sol::object value_from_payload(sol::state_view lua, const ImGuiPayload* payload)
{
    if (payload->DataSize != sizeof(drag_drop_identifier))
        return sol::lua_nil;

    drag_drop_identifier drag_drop_id;
    std::memcpy(&drag_drop_id, payload->Data, sizeof(drag_drop_identifier));

    auto globals = lua.globals();
    if (globals["__imgui_drag_drop_id"] != drag_drop_id)
        return sol::lua_nil;

    return globals["__imgui_drag_drop_value"];
}

sol::object AcceptDragDropPayload(sol::this_state s, const char* type, ImGuiDragDropFlags flags = 0) {
    sol::state_view lua{s};
    auto payload = ImGui::AcceptDragDropPayload(type, flags);
    if (payload) return value_from_payload(lua, payload);
    return sol::lua_nil;
};


void add_imgui_drag_and_drop(sol::table& imgui)
{
    imgui.new_enum<ImGuiDragDropFlags_>("DragDropFlags", {
        {"None",                     ImGuiDragDropFlags_None},
        {"SourceNoPreviewTooltip",   ImGuiDragDropFlags_SourceNoPreviewTooltip},
        {"SourceNoDisableHover",     ImGuiDragDropFlags_SourceNoDisableHover},
        {"SourceNoHoldToOpenOthers", ImGuiDragDropFlags_SourceNoHoldToOpenOthers},
        {"SourceAllowNullID",        ImGuiDragDropFlags_SourceAllowNullID},
        {"SourceExtern",             ImGuiDragDropFlags_SourceExtern},
        {"SourceAutoExpirePayload",  ImGuiDragDropFlags_SourceAutoExpirePayload},
        {"AcceptBeforeDelivery",     ImGuiDragDropFlags_AcceptBeforeDelivery},
        {"AcceptNoDrawDefaultRect",  ImGuiDragDropFlags_AcceptNoDrawDefaultRect},
        {"AcceptNoPreviewTooltip",   ImGuiDragDropFlags_AcceptNoPreviewTooltip},
        {"AcceptPeekOnly",           ImGuiDragDropFlags_AcceptPeekOnly},
    });

    imgui.set_function("BeginDragDropSource",
        sol::overload(
            []() { return ImGui::BeginDragDropSource(); },
            sol::resolve<bool(ImGuiDragDropFlags)>(ImGui::BeginDragDropSource)
        ));

    imgui.set_function("SetDragDropPayload",
        sol::overload(
            [](sol::this_state s, const char* type, sol::object payload) { SetDragDropPayload(s, type, payload); },
            sol::resolve<bool(sol::this_state, const char*, sol::object, ImGuiCond)>(SetDragDropPayload)
        ));

    imgui.set_function("EndDragDropSource", sol::resolve<void()>(ImGui::EndDragDropSource));

    imgui.set_function("AcceptDragDropPayload",
        sol::overload(
            [](sol::this_state s, const char* type) { return AcceptDragDropPayload(s, type); },
            AcceptDragDropPayload
        ));

    imgui.set_function("BeginDragDropTarget", sol::resolve<bool()>(ImGui::BeginDragDropTarget));
    imgui.set_function("EndDragDropTarget", sol::resolve<void()>(ImGui::EndDragDropTarget));
    imgui.set_function("GetDragDropPayload",
        [](sol::this_state s) -> sol::object {
            sol::state_view lua{s};
            auto payload = ImGui::GetDragDropPayload();
            if (!payload)
                return sol::lua_nil;

            return value_from_payload(lua, payload);
        });
}
