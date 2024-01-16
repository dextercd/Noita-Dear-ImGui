#ifndef NOITA_IMGUI_FONTS_HPP
#define NOITA_IMGUI_FONTS_HPP

#include <string>

enum class embedded_fonts {
    noita_pixel,
    noita_pixel_1_4,
    noita_pixel_1_8,
    imgui,
    monospace,
    end_,
};

void add_fonts(const std::string& mod_path);

#endif // Header guard
