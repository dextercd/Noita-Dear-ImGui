#ifndef NOITA_IMGUI_FONTS_HPP
#define NOITA_IMGUI_FONTS_HPP

#include <string>

enum class embedded_fonts {
    noita_pixel = 0,
    noita_pixel_1_4 = 1,
    noita_pixel_1_8 = 2,
    imgui = 3,
    monospace = 4,
    glyph = 5,
    end_,
};

void add_fonts(const std::string& mod_path, float scale, bool pixel_no_anti_aliasing);

#endif // Header guard
