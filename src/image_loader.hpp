#ifndef NOITA_IMGUI_IMAGE_LOADER_HPP
#define NOITA_IMGUI_IMAGE_LOADER_HPP

#include <optional>
#include <string>

extern void (*virtual_image_size)(const char* name, int* size);
extern void (*virtual_image_data)(int id, int width, int height, int* data_out);

struct image {
    void* handle;
    int width;
    int height;
};

std::optional<image> get_image(std::string path);

void unload_unused_images();

#endif // Header guard
