#include <tuple>
#include <optional>

#include <sol/sol.hpp>
#include <imgui.h>

#include "../fonts.hpp"

void add_imgui_font(sol::table& imgui)
{
    auto font_config_type = imgui.new_usertype<ImFontConfig>("FontConfig", sol::no_constructor,
        "FontNo", sol::readonly(&ImFontConfig::FontNo),
        "SizePixels", sol::readonly(&ImFontConfig::SizePixels),
        "OversampleH", sol::readonly(&ImFontConfig::OversampleH),
        "OversampleV", sol::readonly(&ImFontConfig::OversampleV),
        "PixelSnapH", sol::readonly(&ImFontConfig::PixelSnapH),
        "GlyphExtraSpacing_x", sol::property([](const ImFontConfig& cfg) { return cfg.GlyphExtraSpacing.x; }),
        "GlyphExtraSpacing_y", sol::property([](const ImFontConfig& cfg) { return cfg.GlyphExtraSpacing.y; }),
        "GlyphOffset_x", sol::property([](const ImFontConfig& cfg) { return cfg.GlyphOffset.x; }),
        "GlyphOffset_y", sol::property([](const ImFontConfig& cfg) { return cfg.GlyphOffset.y; }),
        "GlyphMinAdvanceX", sol::readonly(&ImFontConfig::GlyphMinAdvanceX),
        "GlyphMaxAdvanceX", sol::readonly(&ImFontConfig::GlyphMaxAdvanceX),
        "MergeMode", sol::readonly(&ImFontConfig::MergeMode),
        "FontBuilderFlags", sol::readonly(&ImFontConfig::FontBuilderFlags),
        "RasterizerMultiply", sol::readonly(&ImFontConfig::RasterizerMultiply),
        "RasterizerDensity", sol::readonly(&ImFontConfig::RasterizerDensity),
        "EllipsisChar", sol::readonly(&ImFontConfig::EllipsisChar)
    );

    auto font_type = imgui.new_usertype<ImFont>("Font", sol::no_constructor,
        // Member variables
        "IndexAdvanceX", sol::readonly(&ImFont::IndexAdvanceX),
        "FallbackAdvanceX", sol::readonly(&ImFont::FallbackAdvanceX),
        "FontSize", sol::readonly(&ImFont::FontSize),
        "IndexLookup", sol::readonly(&ImFont::IndexLookup),
        "ConfigData", sol::readonly(&ImFont::ConfigData),
        "ConfigDataCount", sol::readonly(&ImFont::ConfigDataCount),
        "FallbackChar", sol::readonly(&ImFont::FallbackChar),
        "EllipsisChar", sol::readonly(&ImFont::EllipsisChar),
        "EllipsisCharCount", sol::readonly(&ImFont::EllipsisCharCount),
        "EllipsisWidth", sol::readonly(&ImFont::EllipsisWidth),
        "EllipsisCharStep", sol::readonly(&ImFont::EllipsisCharStep),
        "DirtyLookupTables", sol::readonly(&ImFont::DirtyLookupTables),
        "Scale", sol::readonly(&ImFont::Scale),
        "Ascent", sol::readonly(&ImFont::Ascent),
        "Descent", sol::readonly(&ImFont::Descent),
        "MetricsTotalSurface", sol::readonly(&ImFont::MetricsTotalSurface),
        // Member functions
        "GetCharAdvance", &ImFont::GetCharAdvance,
        "IsLoaded", &ImFont::IsLoaded,
        "GetDebugName", &ImFont::GetDebugName
    );

    font_type.set_function("CalcTextSizeA",
        [](ImFont& font, float size, float max_width, float wrap_width,
           std::string_view text, std::optional<std::size_t> length)
        {
            auto end = text.data() + length.value_or(text.size());
            const char* remaining;
            auto result = font.CalcTextSizeA(
                    size, max_width, wrap_width,
                    text.data(), end,
                    &remaining);

            return std::tuple{result.x, result.y, end - remaining};
        });

    font_type.set_function("CalcWordWrapPositionA",
        [](const ImFont& font, float scale,
           std::string_view text, std::optional<std::size_t> length,
           float wrap_width)
        {
            auto len = length.value_or(text.size());
            return font.CalcWordWrapPositionA(scale, text.data(), text.data() + len, wrap_width) - text.data();
        });

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

    imgui.set_function("GetFont", sol::resolve<ImFont*()>(ImGui::GetFont));

    imgui.set_function("GetFontSize", sol::resolve<float()>(ImGui::GetFontSize));

    imgui.set_function("CalcTextSize",
        [](std::string_view text, std::optional<std::size_t> length,
           std::optional<bool> hide_text_after_double_hash,
           std::optional<float> wrap_width)
        {
            auto end = text.data() + length.value_or(text.size());
            auto size = ImGui::CalcTextSize(
                    text.data(), end,
                    hide_text_after_double_hash.value_or(false),
                    wrap_width.value_or(-1.0f));
            return std::tuple{size.x, size.y};
        });
}
