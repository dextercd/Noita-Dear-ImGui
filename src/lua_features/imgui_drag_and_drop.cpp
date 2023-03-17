#include <sol/sol.hpp>
#include <imgui.h>
#include <iostream>

enum class drag_drop_type {
    boolean,
    string,
    number,
    object
};

using drag_drop_identifier = unsigned int;

namespace {
std::string string_data;
}

bool SetDragDropPayload(sol::this_state s, const char* type, sol::object payload, ImGuiCond cond = 0)
{
    static drag_drop_identifier drag_drop_id = 0;

    sol::state_view lua{s};
    auto globals = lua.globals();

    if (payload.is<bool>()) {
        auto data_type = drag_drop_type::boolean;
        auto value = payload.as<bool>();

        char data[sizeof(data_type) + sizeof(value)];
        std::memcpy(data, &data_type, sizeof(data_type));
        std::memcpy(data + sizeof(data_type), &value, sizeof(value));

        return ImGui::SetDragDropPayload(type, &data, sizeof(data), cond);
    } else if (payload.is<std::string_view>()) {
        auto data_type = drag_drop_type::string;
        bool ret = ImGui::SetDragDropPayload(type, &data_type, sizeof(data_type), cond);
        if (ret)
            string_data = payload.as<std::string>();

        return ret;
    } else if (payload.is<double>()) {
        auto data_type = drag_drop_type::number;
        auto value = payload.as<double>();

        char data[sizeof(data_type) + sizeof(value)];
        std::memcpy(data, &data_type, sizeof(data_type));
        std::memcpy(data + sizeof(data_type), &value, sizeof(value));

        return ImGui::SetDragDropPayload(type, &data, sizeof(data), cond);
    } else {
        auto data_type = drag_drop_type::object;
        auto value = drag_drop_id;

        char data[sizeof(data_type) + sizeof(value)];
        std::memcpy(data, &data_type, sizeof(data_type));
        std::memcpy(data + sizeof(data_type), &value, sizeof(value));

        bool ret = ImGui::SetDragDropPayload(type, &data, sizeof(data), cond);
        if (ret) {
            globals["__imgui_drag_drop_id"] = value;
            globals["__imgui_drag_drop_value"] = payload;
            ++drag_drop_id;
        }

        return ret;
    }
}

sol::object value_from_payload(sol::state_view lua, const ImGuiPayload* payload)
{
    if (payload->DataSize < sizeof(drag_drop_type))
        return sol::lua_nil;

    drag_drop_type data_type;
    std::memcpy(&data_type, payload->Data, sizeof(data_type));

    if (data_type == drag_drop_type::boolean &&
        payload->DataSize == sizeof(data_type) + sizeof(bool))
    {
        bool value;
        std::memcpy(
            &value,
            (const char*)payload->Data + sizeof(data_type),
            sizeof(value));

        return sol::make_object(lua, value);
    }

    if (data_type == drag_drop_type::string &&
        payload->DataSize == sizeof(data_type))
    {
        return sol::make_object(lua, string_data);
    }

    if (data_type == drag_drop_type::number &&
        payload->DataSize == sizeof(data_type) + sizeof(double))
    {
        double value;
        std::memcpy(
            &value,
            (const char*)payload->Data + sizeof(data_type),
            sizeof(value));

        return sol::make_object(lua, value);
    }

    if (data_type == drag_drop_type::object &&
        payload->DataSize == sizeof(data_type) + sizeof(drag_drop_identifier))
    {
        drag_drop_identifier drag_drop_id;
        std::memcpy(
            &drag_drop_id,
            (const char*)payload->Data + sizeof(data_type),
            sizeof(drag_drop_identifier));

        auto globals = lua.globals();
        if (globals["__imgui_drag_drop_id"] != drag_drop_id)
            return sol::lua_nil;

        return globals["__imgui_drag_drop_value"];
    }

    // Should never happen..
    std::cerr << "Unknown drag drop type/size: " << (int)data_type << '/' << payload->DataSize << '\n';
    return sol::lua_nil;
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
            sol::resolve<sol::object(sol::this_state s, const char* type, ImGuiDragDropFlags)>(AcceptDragDropPayload)
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
