#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

#include "../fonts.hpp"

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
        []() -> ImFont* {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[(int)embedded_fonts::noita_pixel];
        });

    imgui.set_function("GetNoitaFont1_4x",
        []() -> ImFont* {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[(int)embedded_fonts::noita_pixel_1_4];
        });

    imgui.set_function("GetNoitaFont1_8x",
        []() -> ImFont* {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[(int)embedded_fonts::noita_pixel_1_8];
        });

    imgui.set_function("GetImGuiFont",
        []() -> ImFont* {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[(int)embedded_fonts::imgui];
        });

    imgui.set_function("GetMonospaceFont",
        []() -> ImFont* {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[(int)embedded_fonts::monospace];
        });

    imgui.set_function("GetGlyphFont",
        []() -> ImFont* {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[(int)embedded_fonts::glyph];
        });

    imgui.set_function("GetNotoFont",
        []() -> ImFont* {
            auto& io = ImGui::GetIO();
            return io.Fonts->Fonts[(int)embedded_fonts::noto];
        });

    imgui.set_function("PushFont", sol::resolve<void(ImFont*)>(ImGui::PushFont));
    imgui.set_function("PopFont", sol::resolve<void()>(ImGui::PopFont));

    imgui.set_function("GetFontSize", sol::resolve<float()>(ImGui::GetFontSize));
}
