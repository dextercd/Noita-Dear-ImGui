#include <string>

#include <sol/sol.hpp>
#include <imgui.h>

#include "../image_loader.hpp"

struct lua_image {
    std::string path;
    int width = -1;
    int height = -1;

    void* get_handle()
    {
        auto img = get_image(path);
        if (!img)
            return nullptr;

        // Update width/height
        width = img->width;
        height = img->height;

        return img->handle;
    }
};

void add_imgui_images(sol::table& imgui)
{
    imgui.new_usertype<lua_image>("LuaImage",
        "path", sol::readonly(&lua_image::path),
        "width", sol::readonly(&lua_image::width),
        "height", sol::readonly(&lua_image::height)
    );

    imgui.set_function("LoadImage",
        [](std::string image_path) -> std::optional<lua_image> {
            lua_image image{.path = image_path};
            // Sets width/height and verifies it could be loaded
            if (image.get_handle()) {
                return image;
            }

            return std::nullopt;
        });

    // This API SUCKS but no one has the power to stop me

    imgui.set_function("Image",
        sol::overload(
            [](lua_image& img, float size_w, float size_h) {
                if (auto h = img.get_handle(); h) ImGui::Image(h, {size_w, size_h});
            },
            [](lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y) {
                if (auto h = img.get_handle(); h) ImGui::Image(h, {size_w, size_h}, {uv0_x, uv0_y});
            },
            [](lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y, float uv1_x, float uv1_y) {
                if (auto h = img.get_handle(); h) ImGui::Image(h, {size_w, size_h}, {uv0_x, uv0_y}, {uv1_x, uv1_y});
            },
            [](lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y, float uv1_x, float uv1_y, float tint_col_r, float tint_col_g, float tint_col_b, float tint_col_a) {
                if (auto h = img.get_handle(); h) ImGui::Image(h, {size_w, size_h}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, {tint_col_r, tint_col_g, tint_col_b, tint_col_a});
            },
            [](lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y, float uv1_x, float uv1_y, float tint_col_r, float tint_col_g, float tint_col_b, float tint_col_a, float border_col_r, float border_col_g, float border_col_b, float border_col_a) {
                if (auto h = img.get_handle(); h) ImGui::Image(h, {size_w, size_h}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, {tint_col_r, tint_col_g, tint_col_b, tint_col_a}, {border_col_r, border_col_g, border_col_b, border_col_a});
            }));

    imgui.set_function("ImageButton",
        sol::overload(
            [](const char* str_id, lua_image& img, float size_w, float size_h) -> std::optional<bool> {
                if (auto h = img.get_handle(); h) return ImGui::ImageButton(str_id, h, {size_w, size_h});
                return std::nullopt;
            },
            [](const char* str_id, lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y) -> std::optional<bool> {
                if (auto h = img.get_handle(); h) return ImGui::ImageButton(str_id, h, {size_w, size_h}, {uv0_x, uv0_y});
                return std::nullopt;
            },
            [](const char* str_id, lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y, float uv1_x, float uv1_y) -> std::optional<bool> {
                if (auto h = img.get_handle(); h) return ImGui::ImageButton(str_id, h, {size_w, size_h}, {uv0_x, uv0_y}, {uv1_x, uv1_y});
                return std::nullopt;
            },
            [](const char* str_id, lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y, float uv1_x, float uv1_y, float bg_col_r, float bg_col_g, float bg_col_b, float bg_col_a) -> std::optional<bool> {
                if (auto h = img.get_handle(); h) return ImGui::ImageButton(str_id, h, {size_w, size_h}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, {bg_col_r, bg_col_g, bg_col_b, bg_col_a});
                return std::nullopt;
            },
            [](const char* str_id, lua_image& img, float size_w, float size_h, float uv0_x, float uv0_y, float uv1_x, float uv1_y, float bg_col_r, float bg_col_g, float bg_col_b, float bg_col_a, float tint_col_r, float tint_col_g, float tint_col_b, float tint_col_a) -> std::optional<bool> {
                if (auto h = img.get_handle(); h) return ImGui::ImageButton(str_id, h, {size_w, size_h}, {uv0_x, uv0_y}, {uv1_x, uv1_y}, {bg_col_r, bg_col_g, bg_col_b, bg_col_a}, {tint_col_r, tint_col_g, tint_col_b, tint_col_a});
                return std::nullopt;
            }));
}
