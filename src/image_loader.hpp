#ifndef NOITA_IMGUI_IMAGE_LOADER_HPP
#define NOITA_IMGUI_IMAGE_LOADER_HPP

#include <optional>
#include <string_view>

struct image {
    void* handle;
    int width;
    int height;
};

std::optional<image> get_image(std::string_view path);

void unload_unused_images();

#endif // Header guard
