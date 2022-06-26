#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

#include <string>
#include <iostream>

struct InputTextCallback_UserData
{
    std::string* str;
};

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        auto str = user_data->str;
        str->resize(data->BufTextLen);
        data->Buf = str->data();
    }

    return 0;
}

bool ImGui_InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.str = str;
    return ImGui::InputText(label, str->data(), str->size() + 1, flags, InputTextCallback, &cb_user_data);
}

bool ImGui_InputTextMultiline(const char* label, std::string* str, ImVec2 size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.str = str;
    return ImGui::InputTextMultiline(label, str->data(), str->size() + 1, size, flags, InputTextCallback, &cb_user_data);
}

bool ImGui_InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.str = str;
    return ImGui::InputTextWithHint(label, hint, str->data(), str->size() + 1, flags, InputTextCallback, &cb_user_data);
}

ImGuiInputTextFlags remove_callback_bits(ImGuiInputTextFlags flags)
{
    return flags & ~(
          ImGuiInputTextFlags_CallbackCompletion
        | ImGuiInputTextFlags_CallbackHistory
        | ImGuiInputTextFlags_CallbackAlways
        | ImGuiInputTextFlags_CallbackCharFilter
        | ImGuiInputTextFlags_CallbackResize
        | ImGuiInputTextFlags_CallbackEdit
    );
}

void add_imgui_text_input(sol::table& imgui)
{
    imgui.new_enum("InputTextFlags",
        "None",                ImGuiInputTextFlags_None,
        "CharsDecimal",        ImGuiInputTextFlags_CharsDecimal,
        "CharsHexadecimal",    ImGuiInputTextFlags_CharsHexadecimal,
        "CharsUppercase",      ImGuiInputTextFlags_CharsUppercase,
        "CharsNoBlank",        ImGuiInputTextFlags_CharsNoBlank,
        "AutoSelectAll",       ImGuiInputTextFlags_AutoSelectAll,
        "EnterReturnsTrue",    ImGuiInputTextFlags_EnterReturnsTrue,
        "CallbackCompletion",  ImGuiInputTextFlags_CallbackCompletion,
        "CallbackHistory",     ImGuiInputTextFlags_CallbackHistory,
        "CallbackAlways",      ImGuiInputTextFlags_CallbackAlways,
        "CallbackCharFilter",  ImGuiInputTextFlags_CallbackCharFilter,
        "AllowTabInput",       ImGuiInputTextFlags_AllowTabInput,
        "CtrlEnterForNewLine", ImGuiInputTextFlags_CtrlEnterForNewLine,
        "NoHorizontalScroll",  ImGuiInputTextFlags_NoHorizontalScroll,
        "AlwaysOverwrite",     ImGuiInputTextFlags_AlwaysOverwrite,
        "ReadOnly",            ImGuiInputTextFlags_ReadOnly,
        "Password",            ImGuiInputTextFlags_Password,
        "NoUndoRedo",          ImGuiInputTextFlags_NoUndoRedo,
        "CharsScientific",     ImGuiInputTextFlags_CharsScientific,
        "CallbackResize",      ImGuiInputTextFlags_CallbackResize,
        "CallbackEdit",        ImGuiInputTextFlags_CallbackEdit
    );

    imgui.set_function("InputText",
        sol::overload(
            [](const char* label, std::string str) { auto ret = ImGui_InputText(label, &str); return std::tuple{ret, str}; },
            [](const char* label, std::string str, ImGuiInputTextFlags flags) { auto ret = ImGui_InputText(label, &str, remove_callback_bits(flags)); return std::tuple{ret, str}; }
        ));

    imgui.set_function("InputTextMultiline",
        sol::overload(
            [](const char* label, std::string str) { auto ret = ImGui_InputTextMultiline(label, &str); return std::tuple{ret, str}; },
            [](const char* label, std::string str, float size_x, float size_y) { auto ret = ImGui_InputTextMultiline(label, &str, {size_x, size_y}); return std::tuple{ret, str}; },
            [](const char* label, std::string str, float size_x, float size_y, ImGuiInputTextFlags flags) { auto ret = ImGui_InputTextMultiline(label, &str, {size_x, size_y}, remove_callback_bits(flags)); return std::tuple{ret, str}; }
        ));

    imgui.set_function("InputTextWithHint",
        sol::overload(
            [](const char* label, const char* hint, std::string str) { auto ret = ImGui_InputTextWithHint(label, hint, &str); return std::tuple{ret, str}; },
            [](const char* label, const char* hint, std::string str, ImGuiInputTextFlags flags) { auto ret = ImGui_InputTextWithHint(label, hint, &str, remove_callback_bits(flags)); return std::tuple{ret, str}; }
        ));

    imgui.set_function("InputFloat",
        sol::overload(
            [](const char* label, float v) { auto ret = ImGui::InputFloat(label, &v); return std::tuple{ret, v}; },
            [](const char* label, float v, float step) { auto ret = ImGui::InputFloat(label, &v, step); return std::tuple{ret, v}; },
            [](const char* label, float v, float step, float step_fast) { auto ret = ImGui::InputFloat(label, &v, step, step_fast); return std::tuple{ret, v}; },
            [](const char* label, float v, float step, float step_fast, const char* format) { auto ret = ImGui::InputFloat(label, &v, step, step_fast, format); return std::tuple{ret, v}; },
            [](const char* label, float v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags) { auto ret = ImGui::InputFloat(label, &v, step, step_fast, format, remove_callback_bits(flags)); return std::tuple{ret, v}; }));

    imgui.set_function("InputFloat2",
        sol::overload(
            [](const char* label, float v1, float v2) { float v[2]{v1, v2}; auto ret = ImGui::InputFloat2(label, v); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, float v1, float v2, const char* format) { float v[2]{v1, v2}; auto ret = ImGui::InputFloat2(label, v, format); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, float v1, float v2, const char* format, ImGuiInputTextFlags flags) { float v[2]{v1, v2}; auto ret = ImGui::InputFloat2(label, v, format, remove_callback_bits(flags)); return std::tuple{ret, v[0], v[1]}; }));

    imgui.set_function("InputFloat3",
        sol::overload(
            [](const char* label, float v1, float v2, float v3) { float v[3]{v1, v2, v3}; auto ret = ImGui::InputFloat3(label, v); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, float v1, float v2, float v3, const char* format) { float v[3]{v1, v2, v3}; auto ret = ImGui::InputFloat3(label, v, format); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, float v1, float v2, float v3, const char* format, ImGuiInputTextFlags flags) { float v[3]{v1, v2, v3}; auto ret = ImGui::InputFloat3(label, v, format, remove_callback_bits(flags)); return std::tuple{ret, v[0], v[1], v[2]}; }));

    imgui.set_function("InputFloat4",
        sol::overload(
            [](const char* label, float v1, float v2, float v3, float v4) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::InputFloat4(label, v); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, float v1, float v2, float v3, float v4, const char* format) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::InputFloat4(label, v, format); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, float v1, float v2, float v3, float v4, const char* format, ImGuiInputTextFlags flags) { float v[4]{v1, v2, v3, v4}; auto ret = ImGui::InputFloat4(label, v, format, remove_callback_bits(flags)); return std::tuple{ret, v[0], v[1], v[2], v[3]}; }));

    imgui.set_function("InputInt",
        sol::overload(
            [](const char* label, int v) { auto ret = ImGui::InputInt(label, &v); return std::tuple{ret, v}; },
            [](const char* label, int v, int step) { auto ret = ImGui::InputInt(label, &v, step); return std::tuple{ret, v}; },
            [](const char* label, int v, int step, int step_fast) { auto ret = ImGui::InputInt(label, &v, step, step_fast); return std::tuple{ret, v}; },
            [](const char* label, int v, int step, int step_fast, ImGuiInputTextFlags flags) { auto ret = ImGui::InputInt(label, &v, step, step_fast, remove_callback_bits(flags)); return std::tuple{ret, v}; }));

    imgui.set_function("InputInt2",
        sol::overload(
            [](const char* label, int v1, int v2) { int v[2]{v1, v2}; auto ret = ImGui::InputInt2(label, v); return std::tuple{ret, v[0], v[1]}; },
            [](const char* label, int v1, int v2, ImGuiInputTextFlags flags) { int v[2]{v1, v2}; auto ret = ImGui::InputInt2(label, v, remove_callback_bits(flags)); return std::tuple{ret, v[0], v[1]}; }));

    imgui.set_function("InputInt3",
        sol::overload(
            [](const char* label, int v1, int v2, int v3) { int v[3]{v1, v2, v3}; auto ret = ImGui::InputInt3(label, v); return std::tuple{ret, v[0], v[1], v[2]}; },
            [](const char* label, int v1, int v2, int v3, ImGuiInputTextFlags flags) { int v[3]{v1, v2, v3}; auto ret = ImGui::InputInt3(label, v, remove_callback_bits(flags)); return std::tuple{ret, v[0], v[1], v[2]}; }));

    imgui.set_function("InputInt4",
        sol::overload(
            [](const char* label, int v1, int v2, int v3, int v4) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::InputInt4(label, v); return std::tuple{ret, v[0], v[1], v[2], v[3]}; },
            [](const char* label, int v1, int v2, int v3, int v4, ImGuiInputTextFlags flags) { int v[4]{v1, v2, v3, v4}; auto ret = ImGui::InputInt4(label, v, remove_callback_bits(flags)); return std::tuple{ret, v[0], v[1], v[2], v[3]}; }));

    imgui.set_function("InputDouble",
        sol::overload(
            [](const char* label, double v) { auto ret = ImGui::InputDouble(label, &v); return std::tuple{ret, v}; },
            [](const char* label, double v, double step) { auto ret = ImGui::InputDouble(label, &v, step); return std::tuple{ret, v}; },
            [](const char* label, double v, double step, double step_fast) { auto ret = ImGui::InputDouble(label, &v, step, step_fast); return std::tuple{ret, v}; },
            [](const char* label, double v, double step, double step_fast, const char* format) { auto ret = ImGui::InputDouble(label, &v, step, step_fast, format); return std::tuple{ret, v}; },
            [](const char* label, double v, double step, double step_fast, const char* format, ImGuiInputTextFlags flags) { auto ret = ImGui::InputDouble(label, &v, step, step_fast, format, remove_callback_bits(flags)); return std::tuple{ret, v}; }));
}
