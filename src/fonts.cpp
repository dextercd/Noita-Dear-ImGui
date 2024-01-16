#include <string>

#include <imgui.h>

#include "fonts.hpp"

void add_fonts(const std::string& mod_path)
{
    ImGuiIO& io = ImGui::GetIO();

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
    builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic());  // Includes default ranges
    builder.BuildRanges(&ranges);

    io.Fonts->AddFontFromFileTTF(noita_font_path.c_str(), 20, nullptr, ranges.Data);
    io.Fonts->AddFontFromFileTTF(noita_font_path.c_str(), 28, nullptr, ranges.Data);
    io.Fonts->AddFontFromFileTTF(noita_font_path.c_str(), 36, nullptr, ranges.Data);

    io.Fonts->AddFontDefault();

    io.Fonts->AddFontFromFileTTF(mono_font_path.c_str(), 20, nullptr, io.Fonts->GetGlyphRangesCyrillic());

    io.Fonts->AddFontFromFileTTF(glyph_font_path.c_str(), 14, nullptr, ranges.Data);

    io.Fonts->Build();  // Build with ranges in scope
}
