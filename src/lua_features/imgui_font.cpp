#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_font(sol::table& imgui)
{
    imgui.set_function("GetFontIndex",
        [](std::size_t font_index) -> ImFont* {
            auto& io = ImGui::GetIO();
            if (font_index >= io.Fonts->Fonts.size())
                return nullptr;

            return io.Fonts->Fonts[font_index];
        });

    imgui.set_function("GetNoitaFont",
        []() {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[0];
        });

    imgui.set_function("GetImGuiFont",
        []() {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[1];
        });

    imgui.set_function("PushFont", sol::resolve<void(ImFont*)>(ImGui::PushFont));
    imgui.set_function("PopFont", sol::resolve<void()>(ImGui::PopFont));
}
