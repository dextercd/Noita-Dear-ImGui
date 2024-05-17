#include <string>

#include <imgui.h>
#include <misc/freetype/imgui_freetype.h>

#include "fonts.hpp"

void add_fonts(const std::string& mod_path, float scale, bool pixel_no_anti_aliasing)
{
    auto noita_font_path = mod_path + "/NoitaPixel.ttf";
    auto mono_font_path = mod_path + "/SourceCodePro-Regular.ttf";
    auto glyph_font_path = mod_path + "/NoitaGlyph.ttf";

    // NoitaPixel font glyph ranges
    ImVector<ImWchar> ranges;
    ImFontGlyphRangesBuilder builder;
    builder.AddChar(0x2013); // EN DASH
    builder.AddChar(0x2014); // EM DASH
    builder.AddChar(0x2019); // RIGHT SINGLE QUOTATION MARK
    builder.AddChar(0x201c); // LEFT DOUBLE QUOTATION MARK
    builder.AddChar(0x201d); // RIGHT DOUBLE QUOTATION MARK
    builder.AddChar(0x201e); // DOUBLE LOW-9 QUOTATION MARK
    builder.AddChar(0x2026); // HORIZONTAL ELLIPSIS
    builder.AddChar(0x221e); // INFINITY
    ImWchar latin_extended_a[]{0x100, 0x17f, 0};
    builder.AddRanges(latin_extended_a);
    ImGuiIO& io = ImGui::GetIO();
    builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic());  // Includes default ranges
    builder.BuildRanges(&ranges);

    auto pixelcfg = ImFontConfig{};
    if (pixel_no_anti_aliasing)
        pixelcfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_MonoHinting | ImGuiFreeTypeBuilderFlags_Monochrome;

    // Doesn't make much sense to me, but these size arguments cause the font to
    // be scaled up pixel perfectly. If this breaks then I should look into
    // generating my own .TTF files or load the fonts manually from the .PNG
    // files.
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF(noita_font_path.c_str(), 15.5f * scale, &pixelcfg, ranges.Data);
    io.Fonts->AddFontFromFileTTF(noita_font_path.c_str(), 23.25f * scale, &pixelcfg, ranges.Data);
    io.Fonts->AddFontFromFileTTF(noita_font_path.c_str(), 30 * scale, &pixelcfg, ranges.Data);

    io.Fonts->AddFontDefault();

    io.Fonts->AddFontFromFileTTF(mono_font_path.c_str(), 19 * scale, nullptr, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->AddFontFromFileTTF(glyph_font_path.c_str(), 14 * scale, &pixelcfg, ranges.Data);

    io.Fonts->Build();  // Build with ranges in scope
}
