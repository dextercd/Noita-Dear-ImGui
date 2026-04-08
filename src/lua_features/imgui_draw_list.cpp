#include <optional>
#include <tuple>

#include <sol/sol.hpp>
#include <imgui.h>

#include "../image_loader.hpp"

void add_imgui_draw_list(sol::table& imgui)
{
    imgui.new_enum<ImDrawFlags_>("DrawFlags", {
        {"None", ImDrawFlags_None},
        {"Closed", ImDrawFlags_Closed},
        {"RoundCornersTopLeft", ImDrawFlags_RoundCornersTopLeft},
        {"RoundCornersTopRight", ImDrawFlags_RoundCornersTopRight},
        {"RoundCornersBottomLeft", ImDrawFlags_RoundCornersBottomLeft},
        {"RoundCornersBottomRight", ImDrawFlags_RoundCornersBottomRight},
        {"RoundCornersNone", ImDrawFlags_RoundCornersNone},
        {"RoundCornersTop", ImDrawFlags_RoundCornersTop},
        {"RoundCornersBottom", ImDrawFlags_RoundCornersBottom},
        {"RoundCornersLeft", ImDrawFlags_RoundCornersLeft},
        {"RoundCornersRight", ImDrawFlags_RoundCornersRight},
        {"RoundCornersAll", ImDrawFlags_RoundCornersAll},
    });

    auto draw_list = imgui.new_usertype<ImDrawList>("DrawList", sol::no_constructor);

    draw_list.set_function("PushClipRect",
        [](ImDrawList& dl,
           float clip_rect_min_x, float clip_rect_min_y,
           float clip_rect_max_x, float clip_rect_max_y,
           std::optional<bool> intersect_with_current_clip_rect)
        {
            return dl.PushClipRect(
                {clip_rect_min_x, clip_rect_min_y},
                {clip_rect_max_x, clip_rect_max_y},
                intersect_with_current_clip_rect.value_or(false)
            );
        }
    );
    draw_list.set_function("PushClipRectFullScreen", [](ImDrawList& dl) { return dl.PushClipRectFullScreen(); });
    draw_list.set_function("PopClipRect", [](ImDrawList& dl) { return dl.PopClipRect(); });

    draw_list.set_function("PushTextureID",
        [](ImDrawList& dl, lua_image& img) {
            if (auto h = img.get_handle(); h)
                dl.PushTextureID(h);
        });
    draw_list.set_function("PopTextureID", [](ImDrawList& dl) { return dl.PopTextureID(); });

    draw_list.set_function("GetClipRectMin", [](ImDrawList& dl) { auto r = dl.GetClipRectMin(); return std::tuple{r.x, r.y}; });
    draw_list.set_function("GetClipRectMax", [](ImDrawList& dl) { auto r = dl.GetClipRectMax(); return std::tuple{r.x, r.y}; });

    draw_list.set_function("AddLine",
        [](ImDrawList& dl,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           ImU32 col,
           std::optional<float> thickness)
        {
            return dl.AddLine({p1_x, p1_y}, {p2_x, p2_y}, col, thickness.value_or(1.0f));
        });

    draw_list.set_function("AddRect",
        [](ImDrawList& dl,
           float p_min_x, float p_min_y,
           float p_max_x, float p_max_y,
           ImU32 col,
           std::optional<float> rounding,
           std::optional<ImDrawFlags> flags,
           std::optional<float> thickness)
        {
            return dl.AddRect(
                {p_min_x, p_min_y},
                {p_max_x, p_max_y},
                col,
                rounding.value_or(0.0f),
                flags.value_or(0),
                thickness.value_or(1.0f)
            );
        });

    draw_list.set_function("AddRectFilled",
        [](ImDrawList& dl,
           float p_min_x, float p_min_y,
           float p_max_x, float p_max_y,
           ImU32 col,
           std::optional<float> rounding,
           std::optional<ImDrawFlags> flags)
        {
            return dl.AddRectFilled(
                {p_min_x, p_min_y},
                {p_max_x, p_max_y},
                col,
                rounding.value_or(0.0f),
                flags.value_or(0)
            );
        });

    draw_list.set_function("AddRectFilledMultiColor",
        [](ImDrawList& dl,
           float p_min_x, float p_min_y,
           float p_max_x, float p_max_y,
           ImU32 col_upr_left,
           ImU32 col_upr_right,
           ImU32 col_bot_right,
           ImU32 col_bot_left)
        {
            return dl.AddRectFilledMultiColor(
                {p_min_x, p_min_y},
                {p_max_x, p_max_y},
                col_upr_left,
                col_upr_right,
                col_bot_right,
                col_bot_left
            );
        });

    draw_list.set_function("AddQuad",
        [](ImDrawList& dl,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           float p4_x, float p4_y,
           ImU32 col,
           std::optional<float> thickness)
        {
            return dl.AddQuad(
                {p1_x, p1_y},
                {p2_x, p2_y},
                {p3_x, p3_y},
                {p4_x, p4_y},
                col,
                thickness.value_or(1.0f)
            );
        });

    draw_list.set_function("AddQuadFilled",
        [](ImDrawList& dl,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           float p4_x, float p4_y,
           ImU32 col)
        {
            return dl.AddQuadFilled(
                {p1_x, p1_y},
                {p2_x, p2_y},
                {p3_x, p3_y},
                {p4_x, p4_y},
                col
            );
        });

    draw_list.set_function("AddTriangle",
        [](ImDrawList& dl,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           ImU32 col,
           std::optional<float> thickness)
        {
            return dl.AddTriangle(
                {p1_x, p1_y},
                {p2_x, p2_y},
                {p3_x, p3_y},
                col,
                thickness.value_or(1.0f)
            );
        });

    draw_list.set_function("AddTriangleFilled",
        [](ImDrawList& dl,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           ImU32 col)
        {
            return dl.AddTriangleFilled(
                {p1_x, p1_y},
                {p2_x, p2_y},
                {p3_x, p3_y},
                col
            );
        });

    draw_list.set_function("AddCircle",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius,
           ImU32 col,
           std::optional<int> num_segments,
           std::optional<float> thickness)
        {
            return dl.AddCircle(
                {center_x, center_y},
                radius,
                col,
                num_segments.value_or(0),
                thickness.value_or(1.0f)
            );
        });

    draw_list.set_function("AddCircleFilled",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius,
           ImU32 col,
           std::optional<int> num_segments)
        {
            return dl.AddCircleFilled(
                {center_x, center_y},
                radius,
                col,
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("AddNgon",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius,
           ImU32 col,
           std::optional<int> num_segments,
           std::optional<float> thickness)
        {
            return dl.AddNgon(
                {center_x, center_y},
                radius,
                col,
                num_segments.value_or(0),
                thickness.value_or(1.0f)
            );
        });

    draw_list.set_function("AddNgonFilled",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius,
           ImU32 col,
           std::optional<int> num_segments)
        {
            return dl.AddNgonFilled(
                {center_x, center_y},
                radius,
                col,
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("AddEllipse",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius_x, float radius_y,
           ImU32 col,
           std::optional<float> rot,
           std::optional<int> num_segments,
           std::optional<float> thickness)
        {
            return dl.AddEllipse(
                {center_x, center_y},
                {radius_x, radius_y},
                col,
                rot.value_or(0.0f),
                num_segments.value_or(0),
                thickness.value_or(1.0f)
            );
        });

    draw_list.set_function("AddEllipseFilled",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius_x, float radius_y,
           ImU32 col,
           std::optional<float> rot,
           std::optional<int> num_segments)
        {
            return dl.AddEllipseFilled(
                {center_x, center_y},
                {radius_x, radius_y},
                col,
                rot.value_or(0.0f),
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("AddText",
        sol::overload(
            [](ImDrawList& dl,
               float pos_x, float pos_y,
               ImU32 col,
               std::string_view text)
            {
                return dl.AddText(
                    {pos_x, pos_y},
                    col,
                    text.data(),
                    text.data() + text.size()
                );
            },
            [](ImDrawList& dl,
               const ImFont* font,
               float font_size, 
               float pos_x, float pos_y,
               ImU32 col,
               std::string_view text)
            {
                return dl.AddText(
                    font,
                    font_size,
                    {pos_x, pos_y},
                    col,
                    text.data(),
                    text.data() + text.size()
                );
            }
        ));


    draw_list.set_function("AddBezierCubic",
        [](ImDrawList& dl,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           float p4_x, float p4_y,
           ImU32 col,
           float thickness,
           std::optional<int> num_segments)
        {
            return dl.AddBezierCubic(
                {p1_x, p1_y},
                {p2_x, p2_y},
                {p3_x, p3_y},
                {p4_x, p4_y},
                col,
                thickness,
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("AddBezierQuadratic",
        [](ImDrawList& dl,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           ImU32 col,
           float thickness,
           std::optional<int> num_segments)
        {
            return dl.AddBezierQuadratic(
                {p1_x, p1_y},
                {p2_x, p2_y},
                {p3_x, p3_y},
                col,
                thickness,
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("AddImage",
        [](ImDrawList& dl,
           lua_image& img,
           float p_min_x, float p_min_y,
           float p_max_x, float p_max_y,
           std::optional<float> uv_min_x, std::optional<float> uv_min_y,
           std::optional<float> uv_max_x, std::optional<float> uv_max_y,
           std::optional<ImU32> col)
        {
            if (auto h = img.get_handle(); h)
                dl.AddImage(
                    h,
                    {p_min_x, p_min_y},
                    {p_max_x, p_max_y},
                    {uv_min_x.value_or(0.0f), uv_min_y.value_or(0.0f)},
                    {uv_max_x.value_or(1.0f), uv_max_y.value_or(1.0f)},
                    col.value_or(IM_COL32_WHITE)
                );
        });

    draw_list.set_function("AddImageQuad",
        [](ImDrawList& dl,
           lua_image& img,
           float p1_x, float p1_y,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           float p4_x, float p4_y,
           std::optional<float> uv1_x, std::optional<float> uv1_y,
           std::optional<float> uv2_x, std::optional<float> uv2_y,
           std::optional<float> uv3_x, std::optional<float> uv3_y,
           std::optional<float> uv4_x, std::optional<float> uv4_y,
           std::optional<ImU32> col)
        {
            if (auto h = img.get_handle(); h)
                dl.AddImageQuad(
                    h,
                    {p1_x, p1_y},
                    {p2_x, p2_y},
                    {p3_x, p3_y},
                    {p4_x, p4_y},
                    {uv1_x.value_or(0.0f), uv1_y.value_or(0.0f)},
                    {uv2_x.value_or(1.0f), uv2_y.value_or(0.0f)},
                    {uv3_x.value_or(1.0f), uv3_y.value_or(1.0f)},
                    {uv4_x.value_or(0.0f), uv4_y.value_or(1.0f)},
                    col.value_or(IM_COL32_WHITE)
                );
        });

    draw_list.set_function("AddImageRounded",
        [](ImDrawList& dl,
           lua_image& img,
           float p_min_x, float p_min_y,
           float p_max_x, float p_max_y,
           float uv_min_x, float uv_min_y,
           float uv_max_x, float uv_max_y,
           ImU32 col,
           float rounding,
           std::optional<ImDrawFlags> flags)
        {
            if (auto h = img.get_handle(); h)
                dl.AddImageRounded(
                    h,
                    {p_min_x, p_min_y},
                    {p_max_x, p_max_y},
                    {uv_min_x, uv_min_y},
                    {uv_max_x, uv_max_y},
                    col,
                    rounding,
                    flags.value_or(0)
                );
        });

    draw_list.set_function("PathClear", [](ImDrawList& dl) { return dl.PathClear(); });
    draw_list.set_function("PathLineTo", [](ImDrawList& dl, float pos_x, float pos_y) { return dl.PathLineTo({pos_x, pos_y}); });
    draw_list.set_function("PathLineToMergeDuplicate", [](ImDrawList& dl, float pos_x, float pos_y) { return dl.PathLineToMergeDuplicate({pos_x, pos_y}); });
    draw_list.set_function("PathFillConvex", [](ImDrawList& dl, ImU32 col) { return dl.PathFillConvex(col); });
    draw_list.set_function("PathFillConcave", [](ImDrawList& dl, ImU32 col) { return dl.PathFillConcave(col); });

    draw_list.set_function("PathStroke",
        [](ImDrawList& dl,
           ImU32 col,
           std::optional<ImDrawFlags> flags,
           std::optional<float> thickness)
        {
            return dl.PathStroke(
                col,
                flags.value_or(0),
                thickness.value_or(1.0f)
            );
        });

    draw_list.set_function("PathArcTo",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius,
           float a_min,
           float a_max,
           std::optional<int> num_segments)
        {
            return dl.PathArcTo(
                {center_x, center_y},
                radius,
                a_min,
                a_max,
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("PathArcToFast",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius,
           int a_min_of_12,
           int a_max_of_12)
        {
            return dl.PathArcToFast(
                {center_x, center_y},
                radius,
                a_min_of_12,
                a_max_of_12
            );
        });

    draw_list.set_function("PathEllipticalArcTo",
        [](ImDrawList& dl,
           float center_x, float center_y,
           float radius_x, float radius_y,
           float rot,
           float a_min,
           float a_max,
           std::optional<int> num_segments)
        {
            return dl.PathEllipticalArcTo(
                {center_x, center_y},
                {radius_x, radius_y},
                rot,
                a_min,
                a_max,
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("PathBezierCubicCurveTo",
        [](ImDrawList& dl,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           float p4_x, float p4_y,
           std::optional<int> num_segments)
        {
            return dl.PathBezierCubicCurveTo(
                {p2_x, p2_y},
                {p3_x, p3_y},
                {p4_x, p4_y},
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("PathBezierQuadraticCurveTo",
        [](ImDrawList& dl,
           float p2_x, float p2_y,
           float p3_x, float p3_y,
           std::optional<int> num_segments)
        {
            return dl.PathBezierQuadraticCurveTo(
                {p2_x, p2_y},
                {p3_x, p3_y},
                num_segments.value_or(0)
            );
        });

    draw_list.set_function("PathRect",
        [](ImDrawList& dl,
           float rect_min_x, float rect_min_y,
           float rect_max_x, float rect_max_y,
           std::optional<float> rounding,
           std::optional<ImDrawFlags> flags)
        {
            return dl.PathRect(
                {rect_min_x, rect_min_y},
                {rect_max_x, rect_max_y},
                rounding.value_or(0.0f),
                flags.value_or(0)
            );
        });

    // void  AddPolyline(const ImVec2* points, int num_points, ImU32 col, ImDrawFlags flags, float thickness);
    // void  AddConvexPolyFilled(const ImVec2* points, int num_points, ImU32 col);
    // void  AddConcavePolyFilled(const ImVec2* points, int num_points, ImU32 col);

    imgui.set_function("GetWindowDrawList", sol::resolve<ImDrawList*()>(ImGui::GetWindowDrawList));
    imgui.set_function("GetBackgroundDrawList",
        sol::overload(
            []() { return ImGui::GetBackgroundDrawList(); },
            sol::resolve<ImDrawList*(ImGuiViewport*)>(ImGui::GetBackgroundDrawList)));

    imgui.set_function("GetForegroundDrawList",
        sol::overload(
            []() { return ImGui::GetForegroundDrawList(); },
            sol::resolve<ImDrawList*(ImGuiViewport*)>(ImGui::GetForegroundDrawList)));
}
