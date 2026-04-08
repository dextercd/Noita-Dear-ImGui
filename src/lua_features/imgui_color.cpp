#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

void add_imgui_color(sol::table& imgui)
{
    void          ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);

    imgui.set_function("ColorConvertU32ToFloat4",
        [](ImU32 in_) {
            auto ret = ImGui::ColorConvertU32ToFloat4(in_);
            return std::tuple{ret.x, ret.y, ret.z, ret.w};
        });

    imgui.set_function("ColorConvertFloat4ToU32",
        [](float x, float y, float z, float w) {
            return ImGui::ColorConvertFloat4ToU32({x, y, z, w});
        });

    imgui.set_function("ColorConvertRGBtoHSV",
        [](float r, float g, float b) {
            float h, s, v;
            ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
            return std::tuple{h, s, v};
        });

    imgui.set_function("ColorConvertHSVtoRGB",
        [](float h, float s, float v) {
            float r, g, b;
            ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
            return std::tuple{r, g, b};
        });
}
