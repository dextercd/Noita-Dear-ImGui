#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <backends/imgui_impl_opengl3_loader.h>
#define GL_NEAREST 0x2600

#include "image_loader.hpp"

#include "filesystem.hpp"
#include "stb_image.h"

void (*virtual_image_size)(const char* name, int* image);
void (*virtual_image_data)(int id, int width, int height, int* data_out);

// Owning handle to OpenGL texture
struct gl_image {
    GLuint handle = 0;
    int width = 0;
    int height = 0;

    gl_image() = default;

    gl_image(gl_image&& other)
        : handle{other.handle}
        , width{other.width}
        , height{other.height}
    {
        other.handle = 0;
    }

    gl_image& operator=(gl_image&& other)
    {
        clear();
        handle = other.handle;
        width = other.width;
        height = other.height;
        other.handle = 0;
        return *this;
    }

    void clear()
    {
        if (handle) {
            glDeleteTextures(1, &handle);
            handle = 0;
        }
    }

    ~gl_image()
    {
        clear();
    }
};

// Managing loaded images
std::unordered_map<std::string, gl_image> loaded_images;

// Images used since the last call to unload_unused_images. This way we don't
// keep images loaded for ever.
std::unordered_set<std::string> used_images;

// Images that couldn't be loaded for whatever reason. Don't want to keep doing
// expensive file operations for those paths so we track them in here.
std::unordered_set<std::string> failed_images;

gl_image* add_image(std::string path, int width, int height, const void* data)
{
    gl_image img;
    img.width = width;
    img.height = height;

    glGenTextures(1, &img.handle);
    glBindTexture(GL_TEXTURE_2D, img.handle);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    auto [it, inserted] = loaded_images.insert({std::string{path}, std::move(img)});
    return &it->second;
}

gl_image* load_image(std::string path)
{
    if (virtual_image_size && virtual_image_data) {
        int image[3]{-1, -1, -1};
        virtual_image_size(path.c_str(), image);
        if (image[0] > 0) {
            std::vector<int> image_data(image[1] * image[2]);
            virtual_image_data(image[0], image[1], image[2], image_data.data());
            return add_image(path, image[1], image[2], image_data.data());
        }
    }

    auto& fs = get_fs();
    auto data_ = fs.get_file(path);

    if (!data_)
        return nullptr;

    auto& data = *data_;

    int width = 0;
    int height = 0;
    int channels = 0;
    auto image_data = stbi_load_from_memory(
        (unsigned char*)data.data(), data.size(),
        &width, &height, &channels, 4);

    if (!image_data)
        return nullptr;

    auto image = add_image(path, width, height, image_data);

    stbi_image_free(image_data);

    return image;
}

std::optional<image> get_image(std::string path)
{
    // Couldn't load it earlier, so don't try again
    std::string str_path{path};
    if (failed_images.find(str_path) != std::end(failed_images))
        return std::nullopt;

    gl_image* img = nullptr;

    auto found = loaded_images.find(str_path);
    if (found != std::end(loaded_images)) {
        img = &found->second;
    }

    if (!img)
        img = load_image(path);

    if (!img) {
        // Failed to load
        failed_images.insert(str_path);
        return std::nullopt;
    }

    used_images.insert(str_path);
    return image{
        .handle = (void*)img->handle,
        .width = img->width,
        .height = img->height,
    };
}

void unload_unused_images()
{
    std::unordered_set<std::string> all_images;
    all_images.reserve(loaded_images.size());
    for (auto&& loaded : loaded_images) {
        all_images.insert(loaded.first);
    }

    for (auto&& image : all_images) {
        if (used_images.find(image) == std::end(used_images)) {
            loaded_images.erase(image);
        }
    }

    used_images.clear();
}
