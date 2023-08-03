#include <algorithm>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include <sol/sol.hpp>
#include <imgui.h>
#include <implot.h>

ImVec4 from_optional(
        std::optional<float> r,
        std::optional<float> g,
        std::optional<float> b,
        std::optional<float> a
) {
    if (r && g && b && a)
        return ImVec4{*r, *g, *b, *a};

    return IMPLOT_AUTO_COL;
}

void add_implot(sol::state_view lua, sol::table& imgui)
{
    sol::table implot = lua.create_table();

    implot.new_enum("Axis",
        "X1", ImAxis_X1,
        "X2", ImAxis_X2,
        "X3", ImAxis_X3,
        "Y1", ImAxis_Y1,
        "Y2", ImAxis_Y2,
        "Y3", ImAxis_Y3
    );

    implot.new_enum("PlotFlags",
        "None", ImPlotFlags_None,
        "NoTitle", ImPlotFlags_NoTitle,
        "NoLegend", ImPlotFlags_NoLegend,
        "NoMouseText", ImPlotFlags_NoMouseText,
        "NoInputs", ImPlotFlags_NoInputs,
        "NoMenus", ImPlotFlags_NoMenus,
        "NoBoxSelect", ImPlotFlags_NoBoxSelect,
        "NoChild", ImPlotFlags_NoChild,
        "NoFrame", ImPlotFlags_NoFrame,
        "Equal", ImPlotFlags_Equal,
        "Crosshairs", ImPlotFlags_Crosshairs,
        "CanvasOnly", ImPlotFlags_CanvasOnly
    );

    implot.new_enum("PlotAxisFlags",
        "None", ImPlotAxisFlags_None,
        "NoLabel", ImPlotAxisFlags_NoLabel,
        "NoGridLines", ImPlotAxisFlags_NoGridLines,
        "NoTickMarks", ImPlotAxisFlags_NoTickMarks,
        "NoTickLabels", ImPlotAxisFlags_NoTickLabels,
        "NoInitialFit", ImPlotAxisFlags_NoInitialFit,
        "NoMenus", ImPlotAxisFlags_NoMenus,
        "NoSideSwitch", ImPlotAxisFlags_NoSideSwitch,
        "NoHighlight", ImPlotAxisFlags_NoHighlight,
        "Opposite", ImPlotAxisFlags_Opposite,
        "Foreground", ImPlotAxisFlags_Foreground,
        "Invert", ImPlotAxisFlags_Invert,
        "AutoFit", ImPlotAxisFlags_AutoFit,
        "RangeFit", ImPlotAxisFlags_RangeFit,
        "PanStretch", ImPlotAxisFlags_PanStretch,
        "LockMin", ImPlotAxisFlags_LockMin,
        "LockMax", ImPlotAxisFlags_LockMax,
        "Lock", ImPlotAxisFlags_Lock,
        "NoDecorations", ImPlotAxisFlags_NoDecorations,
        "AuxDefault", ImPlotAxisFlags_AuxDefault
    );

    implot.new_enum("PlotSubplotFlags",
        "None", ImPlotSubplotFlags_None,
        "NoTitle", ImPlotSubplotFlags_NoTitle,
        "NoLegend", ImPlotSubplotFlags_NoLegend,
        "NoMenus", ImPlotSubplotFlags_NoMenus,
        "NoResize", ImPlotSubplotFlags_NoResize,
        "NoAlign", ImPlotSubplotFlags_NoAlign,
        "ShareItems", ImPlotSubplotFlags_ShareItems,
        "LinkRows", ImPlotSubplotFlags_LinkRows,
        "LinkCols", ImPlotSubplotFlags_LinkCols,
        "LinkAllX", ImPlotSubplotFlags_LinkAllX,
        "LinkAllY", ImPlotSubplotFlags_LinkAllY,
        "ColMajor", ImPlotSubplotFlags_ColMajor
    );

    implot.new_enum("PlotLegendFlags",
        "None", ImPlotLegendFlags_None,
        "NoButtons", ImPlotLegendFlags_NoButtons,
        "NoHighlightItem", ImPlotLegendFlags_NoHighlightItem,
        "NoHighlightAxis", ImPlotLegendFlags_NoHighlightAxis,
        "NoMenus", ImPlotLegendFlags_NoMenus,
        "Outside", ImPlotLegendFlags_Outside,
        "Horizontal", ImPlotLegendFlags_Horizontal,
        "Sort", ImPlotLegendFlags_Sort
    );

    implot.new_enum("PlotMouseTextFlags",
        "None", ImPlotMouseTextFlags_None,
        "NoAuxAxes", ImPlotMouseTextFlags_NoAuxAxes,
        "NoFormat", ImPlotMouseTextFlags_NoFormat,
        "ShowAlways", ImPlotMouseTextFlags_ShowAlways
    );

    implot.new_enum("PlotDragToolFlags",
        "None", ImPlotDragToolFlags_None,
        "NoCursors", ImPlotDragToolFlags_NoCursors,
        "NoFit", ImPlotDragToolFlags_NoFit,
        "NoInputs", ImPlotDragToolFlags_NoInputs,
        "Delayed", ImPlotDragToolFlags_Delayed
    );

    implot.new_enum("PlotColormapScaleFlags",
        "None", ImPlotColormapScaleFlags_None,
        "NoLabel", ImPlotColormapScaleFlags_NoLabel,
        "Opposite", ImPlotColormapScaleFlags_Opposite,
        "Invert", ImPlotColormapScaleFlags_Invert
    );

    implot.new_enum("PlotItemFlags",
        "None", ImPlotItemFlags_None,
        "NoLegend", ImPlotItemFlags_NoLegend,
        "NoFit", ImPlotItemFlags_NoFit
    );

    implot.new_enum("PlotLineFlags",
        "None", ImPlotLineFlags_None,
        "Segments", ImPlotLineFlags_Segments,
        "Loop", ImPlotLineFlags_Loop,
        "SkipNaN", ImPlotLineFlags_SkipNaN,
        "NoClip", ImPlotLineFlags_NoClip,
        "Shaded", ImPlotLineFlags_Shaded
    );

    implot.new_enum("PlotScatterFlags",
        "None", ImPlotScatterFlags_None,
        "NoClip", ImPlotScatterFlags_NoClip
    );

    implot.new_enum("PlotStairsFlags",
        "None", ImPlotStairsFlags_None,
        "PreStep", ImPlotStairsFlags_PreStep,
        "Shaded", ImPlotStairsFlags_Shaded
    );

    implot.new_enum("PlotShadedFlags",
        "None", ImPlotShadedFlags_None
    );

    implot.new_enum("PlotBarsFlags",
        "None", ImPlotBarsFlags_None,
        "Horizontal", ImPlotBarsFlags_Horizontal
    );

    implot.new_enum("PlotBarGroupsFlags",
        "None", ImPlotBarGroupsFlags_None,
        "Horizontal", ImPlotBarGroupsFlags_Horizontal,
        "Stacked", ImPlotBarGroupsFlags_Stacked
    );

    implot.new_enum("PlotErrorBarsFlags",
        "None", ImPlotErrorBarsFlags_None,
        "Horizontal", ImPlotErrorBarsFlags_Horizontal
    );

    implot.new_enum("PlotStemsFlags",
        "None", ImPlotStemsFlags_None,
        "Horizontal", ImPlotStemsFlags_Horizontal
    );

    implot.new_enum("PlotInfLinesFlags",
        "None", ImPlotInfLinesFlags_None,
        "Horizontal", ImPlotInfLinesFlags_Horizontal
    );

    implot.new_enum("PlotPieChartFlags",
        "None", ImPlotPieChartFlags_None,
        "Normalize", ImPlotPieChartFlags_Normalize
    );

    implot.new_enum("PlotHeatmapFlags",
        "None", ImPlotHeatmapFlags_None,
        "ColMajor", ImPlotHeatmapFlags_ColMajor
    );

    implot.new_enum("PlotHistogramFlags",
        "None", ImPlotHistogramFlags_None,
        "Horizontal", ImPlotHistogramFlags_Horizontal,
        "Cumulative", ImPlotHistogramFlags_Cumulative,
        "Density", ImPlotHistogramFlags_Density,
        "NoOutliers", ImPlotHistogramFlags_NoOutliers,
        "ColMajor", ImPlotHistogramFlags_ColMajor
    );

    implot.new_enum("PlotDigitalFlags",
        "None", ImPlotDigitalFlags_None
    );

    implot.new_enum("PlotImageFlags",
        "None", ImPlotImageFlags_None
    );

    implot.new_enum("PlotTextFlags",
        "None", ImPlotTextFlags_None,
        "Vertical", ImPlotTextFlags_Vertical
    );

    implot.new_enum("PlotDummyFlags",
        "None", ImPlotDummyFlags_None
    );

    implot.new_enum("PlotCond",
        "None", ImPlotCond_None,
        "Always", ImPlotCond_Always,
        "Once", ImPlotCond_Once
    );

    implot.new_enum("PlotCol",
        "Line", ImPlotCol_Line,
        "Fill", ImPlotCol_Fill,
        "MarkerOutline", ImPlotCol_MarkerOutline,
        "MarkerFill", ImPlotCol_MarkerFill,
        "ErrorBar", ImPlotCol_ErrorBar,
        "FrameBg", ImPlotCol_FrameBg,
        "PlotBg", ImPlotCol_PlotBg,
        "PlotBorder", ImPlotCol_PlotBorder,
        "LegendBg", ImPlotCol_LegendBg,
        "LegendBorder", ImPlotCol_LegendBorder,
        "LegendText", ImPlotCol_LegendText,
        "TitleText", ImPlotCol_TitleText,
        "InlayText", ImPlotCol_InlayText,
        "AxisText", ImPlotCol_AxisText,
        "AxisGrid", ImPlotCol_AxisGrid,
        "AxisTick", ImPlotCol_AxisTick,
        "AxisBg", ImPlotCol_AxisBg,
        "AxisBgHovered", ImPlotCol_AxisBgHovered,
        "AxisBgActive", ImPlotCol_AxisBgActive,
        "Selection", ImPlotCol_Selection,
        "Crosshairs", ImPlotCol_Crosshairs
    );

    implot.new_enum("PlotStyleVar",
        "LineWeight", ImPlotStyleVar_LineWeight,
        "Marker", ImPlotStyleVar_Marker,
        "MarkerSize", ImPlotStyleVar_MarkerSize,
        "MarkerWeight", ImPlotStyleVar_MarkerWeight,
        "FillAlpha", ImPlotStyleVar_FillAlpha,
        "ErrorBarSize", ImPlotStyleVar_ErrorBarSize,
        "ErrorBarWeight", ImPlotStyleVar_ErrorBarWeight,
        "DigitalBitHeight", ImPlotStyleVar_DigitalBitHeight,
        "DigitalBitGap", ImPlotStyleVar_DigitalBitGap,
        "PlotBorderSize", ImPlotStyleVar_PlotBorderSize,
        "MinorAlpha", ImPlotStyleVar_MinorAlpha,
        "MajorTickLen", ImPlotStyleVar_MajorTickLen,
        "MinorTickLen", ImPlotStyleVar_MinorTickLen,
        "MajorTickSize", ImPlotStyleVar_MajorTickSize,
        "MinorTickSize", ImPlotStyleVar_MinorTickSize,
        "MajorGridSize", ImPlotStyleVar_MajorGridSize,
        "MinorGridSize", ImPlotStyleVar_MinorGridSize,
        "PlotPadding", ImPlotStyleVar_PlotPadding,
        "LabelPadding", ImPlotStyleVar_LabelPadding,
        "LegendPadding", ImPlotStyleVar_LegendPadding,
        "LegendInnerPadding", ImPlotStyleVar_LegendInnerPadding,
        "LegendSpacing", ImPlotStyleVar_LegendSpacing,
        "MousePosPadding", ImPlotStyleVar_MousePosPadding,
        "AnnotationPadding", ImPlotStyleVar_AnnotationPadding,
        "FitPadding", ImPlotStyleVar_FitPadding,
        "PlotDefaultSize", ImPlotStyleVar_PlotDefaultSize,
        "PlotMinSize", ImPlotStyleVar_PlotMinSize
    );

    implot.new_enum("PlotScale",
        "Linear", ImPlotScale_Linear,
        "Time", ImPlotScale_Time,
        "Log10", ImPlotScale_Log10,
        "SymLog", ImPlotScale_SymLog
    );

    implot.new_enum("PlotMarker",
        "None", ImPlotMarker_None,
        "Circle", ImPlotMarker_Circle,
        "Square", ImPlotMarker_Square,
        "Diamond", ImPlotMarker_Diamond,
        "Up", ImPlotMarker_Up,
        "Down", ImPlotMarker_Down,
        "Left", ImPlotMarker_Left,
        "Right", ImPlotMarker_Right,
        "Cross", ImPlotMarker_Cross,
        "Plus", ImPlotMarker_Plus,
        "Asterisk", ImPlotMarker_Asterisk
    );

    implot.new_enum("PlotColormap",
        "Deep", ImPlotColormap_Deep,
        "PlotColormap_Dark", ImPlotColormap_Dark,
        "Pastel", ImPlotColormap_Pastel,
        "Paired", ImPlotColormap_Paired,
        "Viridis", ImPlotColormap_Viridis,
        "Plasma", ImPlotColormap_Plasma,
        "Hot", ImPlotColormap_Hot,
        "Cool", ImPlotColormap_Cool,
        "Pink", ImPlotColormap_Pink,
        "Jet", ImPlotColormap_Jet,
        "Twilight", ImPlotColormap_Twilight,
        "RdBu", ImPlotColormap_RdBu,
        "BrBG", ImPlotColormap_BrBG,
        "PiYG", ImPlotColormap_PiYG,
        "Spectral", ImPlotColormap_Spectral,
        "Greys", ImPlotColormap_Greys
    );

    implot.new_enum("PlotLocation",
        "Center", ImPlotLocation_Center,
        "North", ImPlotLocation_North,
        "South", ImPlotLocation_South,
        "West", ImPlotLocation_West,
        "East", ImPlotLocation_East,
        "NorthWest", ImPlotLocation_NorthWest,
        "NorthEast", ImPlotLocation_NorthEast,
        "SouthWest", ImPlotLocation_SouthWest,
        "SouthEast", ImPlotLocation_SouthEast
    );

    implot.new_enum("PlotBin",
        "Sqrt", ImPlotBin_Sqrt,
        "Sturges", ImPlotBin_Sturges,
        "Rice", ImPlotBin_Rice,
        "Scott", ImPlotBin_Scott
    );

    implot.new_usertype<ImPlotPoint>("PlotPoint",
        sol::constructors<ImPlotPoint(), ImPlotPoint(double, double)>(),
        "x", &ImPlotPoint::x,
        "y", &ImPlotPoint::y
    );

    implot.new_usertype<ImPlotRect>("PlotRect",
        sol::constructors<ImPlotRect(), ImPlotRect(double, double, double, double)>(),
        "X", &ImPlotRect::X,
        "Y", &ImPlotRect::Y
    );

    implot.new_usertype<ImPlotRange>("PlotRange",
        sol::constructors<ImPlotRange(), ImPlotRange(double, double)>(),
        "Min", &ImPlotRange::Min,
        "Max", &ImPlotRange::Max
    );

    implot.set_function("BeginPlot",
        sol::overload(
            [](const char* title_id) -> bool { return ImPlot::BeginPlot(title_id); },
            [](const char* title_id, float size_x, float size_y) -> bool { return ImPlot::BeginPlot(title_id, {size_x, size_y}); },
            [](const char* title_id, float size_x, float size_y, ImPlotFlags flags) -> bool { return ImPlot::BeginPlot(title_id, {size_x, size_y}, flags); }));
    implot.set_function("EndPlot", sol::resolve<void()>(ImPlot::EndPlot));

    implot.set_function("BeginSubplots",
        sol::overload(
            [](const char* title_id, int rows, int cols, float size_x, float size_y) -> bool { return ImPlot::BeginSubplots(title_id, rows, cols, {size_x, size_y}); },
            [](const char* title_id, int rows, int cols, float size_x, float size_y, ImPlotSubplotFlags flags) -> bool { return ImPlot::BeginSubplots(title_id, rows, cols, {size_x, size_y}, flags); }));
    implot.set_function("EndSubplots", sol::resolve<void()>(ImPlot::EndSubplots));


    implot.set_function("SetupAxis",
        sol::overload(
            [](ImAxis axis) { ImPlot::SetupAxis(axis); },
            [](ImAxis axis, const char* label) { ImPlot::SetupAxis(axis, label); },
            [](ImAxis axis, const char* label, ImPlotAxisFlags flags) { ImPlot::SetupAxis(axis, label, flags); },
            sol::resolve<void(ImAxis, const char*, ImPlotAxisFlags)>(ImPlot::SetupAxis)));

    implot.set_function("SetupAxisLimits",
        sol::overload(
                [](ImAxis axis, double v_min, double v_max) { ImPlot::SetupAxisLimits(axis, v_min, v_max); },
                sol::resolve<void(ImAxis, double, double, ImPlotCond)>(ImPlot::SetupAxisLimits)));

    // SetupAxisLinks

    implot.set_function("SetupAxisFormat", sol::resolve<void(ImAxis, const char*)>(ImPlot::SetupAxisFormat));

    implot.set_function("SetupAxisTicks",
        sol::overload(
            [](ImAxis axis, std::vector<double> values, std::optional<std::vector<const char*>> labels, std::optional<bool> keep_default) -> void {
                int n_ticks = std::size(values);
                const char* const* lbls = nullptr;
                if (labels) {
                    n_ticks = std::min(std::size(values), std::size(*labels));
                    lbls = std::data(*labels);
                }
                if (keep_default)
                    ImPlot::SetupAxisTicks(axis, std::data(values), n_ticks, lbls, *keep_default);
                else
                    ImPlot::SetupAxisTicks(axis, std::data(values), n_ticks, lbls);
            },
            [](ImAxis axis, double v_min, double v_max, int n_ticks, std::optional<std::vector<const char*>> labels, std::optional<bool> keep_default) {
                const char* const* lbls = nullptr;
                if (labels) {
                    n_ticks = std::min(n_ticks, (int)std::size(*labels));
                    lbls = std::data(*labels);
                }
                if (keep_default)
                    ImPlot::SetupAxisTicks(axis, v_min, v_max, n_ticks, lbls, *keep_default);
                else
                    ImPlot::SetupAxisTicks(axis, v_min, v_max, n_ticks, lbls);
            }
        ));

    implot.set_function("SetupAxisScale", sol::resolve<void(ImAxis, ImPlotScale)>(ImPlot::SetupAxisScale));
    implot.set_function("SetupAxisLimitsConstraints", sol::resolve<void(ImAxis, double, double)>(ImPlot::SetupAxisLimitsConstraints));
    implot.set_function("SetupAxisZoomConstraints", sol::resolve<void(ImAxis, double, double)>(ImPlot::SetupAxisZoomConstraints));

    implot.set_function("SetupAxes",
        sol::overload(
            [](const char* x_label, const char* y_label) { ImPlot::SetupAxes(x_label, y_label); },
            [](const char* x_label, const char* y_label, ImPlotAxisFlags x_flags) { ImPlot::SetupAxes(x_label, y_label, x_flags); },
            sol::resolve<void(const char*, const char*, ImPlotAxisFlags, ImPlotAxisFlags)>(ImPlot::SetupAxes)));

    implot.set_function("SetupAxesLimits",
        sol::overload(
            [](double x_min, double x_max, double y_min, double y_max) { ImPlot::SetupAxesLimits(x_min, x_max, y_min, y_max); },
            sol::resolve<void(double, double, double, double, ImPlotCond)>(ImPlot::SetupAxesLimits)));

    implot.set_function("SetupLegend",
        sol::overload(
            [](ImPlotLocation location) { ImPlot::SetupLegend(location); },
            sol::resolve<void(ImPlotLocation, ImPlotLegendFlags)>(ImPlot::SetupLegend)));

    implot.set_function("SetupMouseText",
        sol::overload(
            [](ImPlotLocation location) { ImPlot::SetupMouseText(location); },
            sol::resolve<void(ImPlotLocation, ImPlotMouseTextFlags)>(ImPlot::SetupMouseText)));

    implot.set_function("SetupFinish", sol::resolve<void()>(ImPlot::SetupFinish));


    implot.set_function("SetNextAxisLimits",
        sol::overload(
            [](ImAxis axis, double v_min, double v_max) { return ImPlot::SetNextAxisLimits(axis, v_min, v_max); },
            sol::resolve<void(ImAxis, double, double, ImPlotCond cond)>(ImPlot::SetNextAxisLimits)));

    implot.set_function("SetNextAxisToFit", sol::resolve<void(ImAxis)>(ImPlot::SetNextAxisToFit));

    implot.set_function("SetNextAxesLimits",
        sol::overload(
            [](double x_min, double x_max, double y_min, double y_max) { return ImPlot::SetNextAxesLimits(x_min, x_max, y_min, y_max); },
            sol::resolve<void(double, double, double, double, ImPlotCond cond)>(ImPlot::SetNextAxesLimits)));

    implot.set_function("SetNextAxesToFit", sol::resolve<void()>(ImPlot::SetNextAxesToFit));


    implot.set_function("PlotLine",
        sol::overload(
            [](const char* label_id, std::vector<double> values) -> void { return ImPlot::PlotLine(label_id, std::data(values), std::size(values)); },
            [](const char* label_id, std::vector<double> values, double xscale) -> void { ImPlot::PlotLine(label_id, std::data(values), std::size(values), xscale); },
            [](const char* label_id, std::vector<double> values, double xscale, double xstart) -> void { ImPlot::PlotLine(label_id, std::data(values), std::size(values), xscale, xstart); },
            [](const char* label_id, std::vector<double> values, double xscale, double xstart, ImPlotLineFlags flags) -> void { ImPlot::PlotLine(label_id, std::data(values), std::size(values), xscale, xstart, flags); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys) { ImPlot::PlotLine(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys))); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, ImPlotLineFlags flags) { ImPlot::PlotLine(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys)), flags); }));

    implot.set_function("PlotScatter",
        sol::overload(
            [](const char* label_id, std::vector<double> values) -> void { return ImPlot::PlotScatter(label_id, std::data(values), std::size(values)); },
            [](const char* label_id, std::vector<double> values, double xscale) -> void { ImPlot::PlotScatter(label_id, std::data(values), std::size(values), xscale); },
            [](const char* label_id, std::vector<double> values, double xscale, double xstart) -> void { ImPlot::PlotScatter(label_id, std::data(values), std::size(values), xscale, xstart); },
            [](const char* label_id, std::vector<double> values, double xscale, double xstart, ImPlotScatterFlags flags) -> void { ImPlot::PlotScatter(label_id, std::data(values), std::size(values), xscale, xstart, flags); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys) { ImPlot::PlotScatter(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys))); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, ImPlotScatterFlags flags) { ImPlot::PlotScatter(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys)), flags); }));

    implot.set_function("PlotStairs",
        sol::overload(
            [](const char* label_id, std::vector<double> values) -> void { return ImPlot::PlotStairs(label_id, std::data(values), std::size(values)); },
            [](const char* label_id, std::vector<double> values, double xscale) -> void { ImPlot::PlotStairs(label_id, std::data(values), std::size(values), xscale); },
            [](const char* label_id, std::vector<double> values, double xscale, double xstart) -> void { ImPlot::PlotStairs(label_id, std::data(values), std::size(values), xscale, xstart); },
            [](const char* label_id, std::vector<double> values, double xscale, double xstart, ImPlotStairsFlags flags) -> void { ImPlot::PlotStairs(label_id, std::data(values), std::size(values), xscale, xstart, flags); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys) { ImPlot::PlotStairs(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys))); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, ImPlotStairsFlags flags) { ImPlot::PlotStairs(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys)), flags); }));

    implot.set_function("PlotBars",
        sol::overload(
            [](const char* label_id, std::vector<double> values) -> void { return ImPlot::PlotBars(label_id, std::data(values), std::size(values)); },
            [](const char* label_id, std::vector<double> values, double bar_size) -> void { ImPlot::PlotBars(label_id, std::data(values), std::size(values), bar_size); },
            [](const char* label_id, std::vector<double> values, double bar_size, double shift) -> void { ImPlot::PlotBars(label_id, std::data(values), std::size(values), bar_size, shift); },
            [](const char* label_id, std::vector<double> values, double bar_size, double shift, ImPlotBarsFlags flags) -> void { ImPlot::PlotBars(label_id, std::data(values), std::size(values), bar_size, shift, flags); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, double bar_size) { ImPlot::PlotBars(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys)), bar_size); },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, ImPlotBarsFlags flags, double bar_size) { ImPlot::PlotBars(label_id, std::data(xs), std::data(ys), std::min(std::size(xs), std::size(ys)), bar_size, flags); }));

    // PlotBarGroups

    implot.set_function("PlotErrorBars",
        sol::overload(
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, std::vector<double> err, std::optional<ImPlotErrorBarsFlags> flags) -> void {
                auto count = (int)std::min({std::size(xs), std::size(ys), std::size(err)});
                if (flags)
                    return ImPlot::PlotErrorBars(label_id, std::data(xs), std::data(ys), std::data(err), count, *flags);
                else
                    return ImPlot::PlotErrorBars(label_id, std::data(xs), std::data(ys), std::data(err), count);
            },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, std::vector<double> neg, std::vector<double> pos, std::optional<ImPlotErrorBarsFlags> flags) -> void {
                auto count = (int)std::min({std::size(xs), std::size(ys), std::size(neg), std::size(pos)});
                if (flags)
                    return ImPlot::PlotErrorBars(label_id, std::data(xs), std::data(ys), std::data(neg), std::data(pos), count, *flags);
                else
                    return ImPlot::PlotErrorBars(label_id, std::data(xs), std::data(ys), std::data(neg), std::data(pos), count);
            }
        ));

    implot.set_function("PlotStems",
        sol::overload(
            [](const char* label_id, std::vector<double> values, std::optional<double> ref, std::optional<double> scale, std::optional<double> start, std::optional<ImPlotStemsFlags> flags) -> void {
                auto count = (int)std::size(values);

                if (!ref) return ImPlot::PlotStems(label_id, std::data(values), count);
                if (!scale) return ImPlot::PlotStems(label_id, std::data(values), count, *ref);
                if (!start) return ImPlot::PlotStems(label_id, std::data(values), count, *ref, *scale);
                if (!flags) return ImPlot::PlotStems(label_id, std::data(values), count, *ref, *scale, *start);
                return ImPlot::PlotStems(label_id, std::data(values), count, *ref, *scale, *start, *flags);
            },
            [](const char* label_id, std::vector<double> xs, std::vector<double> ys, std::optional<double> ref, std::optional<ImPlotStemsFlags> flags) {
                auto count = (int)std::min(std::size(xs), std::size(ys));
                if (!ref) return ImPlot::PlotStems(label_id, std::data(xs), std::data(ys), count);
                if (!flags) return ImPlot::PlotStems(label_id, std::data(xs), std::data(ys), count, *ref);
                return ImPlot::PlotStems(label_id, std::data(xs), std::data(ys), count, *ref, *flags);
            }
        ));

    implot.set_function("PlotInfLines",
        [](const char* label_id, std::vector<double> values, std::optional<ImPlotInfLinesFlags> flags) -> void {
            if (!flags) return ImPlot::PlotInfLines(label_id, std::data(values), std::size(values));
            return ImPlot::PlotInfLines(label_id, std::data(values), std::size(values), *flags);
        });

    implot.set_function("PlotPieChart",
        [](std::vector<const char*> label_ids, std::vector<double> values, double x, double y, double radius, std::optional<const char*> label_fmt, std::optional<double> angle0, std::optional<ImPlotPieChartFlags> flags) -> void {
            auto count = (int)std::min(std::size(label_ids), std::size(values));
            if (!label_fmt) return ImPlot::PlotPieChart(std::data(label_ids), std::data(values), count, x, y, radius);
            if (!angle0) return ImPlot::PlotPieChart(std::data(label_ids), std::data(values), count, x, y, radius, *label_fmt);
            if (!flags) return ImPlot::PlotPieChart(std::data(label_ids), std::data(values), count, x, y, radius, *label_fmt, *angle0);
            return ImPlot::PlotPieChart(std::data(label_ids), std::data(values), count, x, y, radius, *label_fmt, *angle0, *flags);
        });

    implot.set_function("PlotHeatmap",
        [](const char* label_id, std::vector<double> values, int rows, int cols,
            std::optional<double> scale_min, std::optional<double> scale_max,
            std::optional<const char*> label_fmt,
            std::optional<ImPlotPoint> bounds_min, std::optional<ImPlotPoint> bounds_max,
            std::optional<ImPlotHeatmapFlags> flags) -> void
        {
            if (std::size(values) < rows * cols)
                return;

            if (!scale_min) return ImPlot::PlotHeatmap(label_id, std::data(values), rows, cols);
            if (!scale_max) return ImPlot::PlotHeatmap(label_id, std::data(values), rows, cols, *scale_min);
            if (!label_fmt) return ImPlot::PlotHeatmap(label_id, std::data(values), rows, cols, *scale_min, *scale_max);
            if (!bounds_min) return ImPlot::PlotHeatmap(label_id, std::data(values), rows, cols, *scale_min, *scale_max, *label_fmt);
            if (!bounds_max) return ImPlot::PlotHeatmap(label_id, std::data(values), rows, cols, *scale_min, *scale_max, *label_fmt, *bounds_min);
            if (!flags) return ImPlot::PlotHeatmap(label_id, std::data(values), rows, cols, *scale_min, *scale_max, *label_fmt, *bounds_min, *bounds_max);
            return ImPlot::PlotHeatmap(label_id, std::data(values), rows, cols, *scale_min, *scale_max, *label_fmt, *bounds_min, *bounds_max, *flags);
        });

    implot.set_function("PlotHistogram",
        [](const char* label_id, std::vector<double> values, std::optional<ImPlotBin> bins, std::optional<double> bar_scale, std::optional<ImPlotRange> range, std::optional<ImPlotHistogramFlags> flags) -> double {
            auto count = (int)std::size(values);
            if (!bins) return ImPlot::PlotHistogram(label_id, std::data(values), count);
            if (!bar_scale) return ImPlot::PlotHistogram(label_id, std::data(values), count, *bins);
            if (!range) return ImPlot::PlotHistogram(label_id, std::data(values), count, *bins, *bar_scale);
            if (!flags) return ImPlot::PlotHistogram(label_id, std::data(values), count, *bins, *bar_scale, *range);
            return ImPlot::PlotHistogram(label_id, std::data(values), count, *bins, *bar_scale, *range, *flags);
        });

    implot.set_function("PlotHistogram2D",
        [](const char* label_id, std::vector<double> xs, std::vector<double> ys, std::optional<ImPlotBin> x_bins, std::optional<ImPlotBin> y_bins, std::optional<ImPlotRect> range, std::optional<ImPlotHistogramFlags> flags) -> double {
            auto count = (int)std::min(std::size(xs), std::size(ys));
            if (!x_bins) return ImPlot::PlotHistogram2D(label_id, std::data(xs), std::data(ys), count);
            if (!y_bins) return ImPlot::PlotHistogram2D(label_id, std::data(xs), std::data(ys), count, *x_bins);
            if (!range) return ImPlot::PlotHistogram2D(label_id, std::data(xs), std::data(ys), count, *x_bins, *y_bins);
            if (!flags) return ImPlot::PlotHistogram2D(label_id, std::data(xs), std::data(ys), count, *x_bins, *y_bins, *range);
            return ImPlot::PlotHistogram2D(label_id, std::data(xs), std::data(ys), count, *x_bins, *y_bins, *range, *flags);
        });

    implot.set_function("PlotDigital",
        [](const char* label_id, std::vector<double> xs, std::vector<double> ys, std::optional<ImPlotDigitalFlags> flags) -> void {
            auto count = (int)std::min(std::size(xs), std::size(ys));
            if (!flags) return ImPlot::PlotDigital(label_id, std::data(xs), std::data(ys), count);
            return ImPlot::PlotDigital(label_id, std::data(xs), std::data(ys), count, *flags);
        });

    implot.set_function("PlotText",
        sol::overload(
            [](const char* text, double x, double y) -> void { return ImPlot::PlotText(text, x, y); },
            [](const char* text, double x, double y, float pix_offset_x, float pix_offset_y) { ImPlot::PlotText(text, x, y, {pix_offset_x, pix_offset_y}); },
            [](const char* text, double x, double y, float pix_offset_x, float pix_offset_y, ImPlotTextFlags flags) { ImPlot::PlotText(text, x, y, {pix_offset_x, pix_offset_y}, flags); }));

    implot.set_function("PlotDummy",
        sol::overload(
            [](const char* label_id) -> void { return ImPlot::PlotDummy(label_id); },
            [](const char* label_id, ImPlotDummyFlags flags) { ImPlot::PlotDummy(label_id, flags); }));


    implot.set_function("DragPoint",
        sol::overload(
            [](int id, double x, double y, float r, float g, float b, float a) -> std::tuple<bool, double, double> { auto ret = ImPlot::DragPoint(id, &x, &y, {r, g, b, a}); return std::tuple{ret, x, y}; },
            [](int id, double x, double y, float r, float g, float b, float a, float size) { auto ret = ImPlot::DragPoint(id, &x, &y, {r, g, b, a}, size); return std::tuple{ret, x, y}; },
            [](int id, double x, double y, float r, float g, float b, float a, float size, ImPlotDragToolFlags flags) { auto ret = ImPlot::DragPoint(id, &x, &y, {r, g, b, a}, size, flags); return std::tuple{ret, x, y}; }));

    implot.set_function("DragLineX",
        sol::overload(
            [](int id, double x, float r, float g, float b, float a) -> std::tuple<bool, double> { auto ret = ImPlot::DragLineX(id, &x, {r, g, b, a}); return std::tuple{ret, x}; },
            [](int id, double x, float r, float g, float b, float a, float thickness) { auto ret = ImPlot::DragLineX(id, &x, {r, g, b, a}, thickness); return std::tuple{ret, x}; },
            [](int id, double x, float r, float g, float b, float a, float thickness, ImPlotDragToolFlags flags) { auto ret = ImPlot::DragLineX(id, &x, {r, g, b, a}, thickness, flags); return std::tuple{ret, x}; }));

    implot.set_function("DragLineY",
        sol::overload(
            [](int id, double y, float r, float g, float b, float a) -> std::tuple<bool, double> { auto ret = ImPlot::DragLineY(id, &y, {r, g, b, a}); return std::tuple{ret, y}; },
            [](int id, double y, float r, float g, float b, float a, float thickness) { auto ret = ImPlot::DragLineY(id, &y, {r, g, b, a}, thickness); return std::tuple{ret, y}; },
            [](int id, double y, float r, float g, float b, float a, float thickness, ImPlotDragToolFlags flags) { auto ret = ImPlot::DragLineY(id, &y, {r, g, b, a}, thickness, flags); return std::tuple{ret, y}; }));

    implot.set_function("DragRect",
        sol::overload(
            [](int id, double x1, double y1, double x2, double y2, float r, float g, float b, float a) -> std::tuple<bool, double, double, double, double> { auto ret = ImPlot::DragRect(id, &x1, &y1, &x2, &y2, {r, g, b, a}); return std::tuple{ret, x1, y1, x2, y2}; },
            [](int id, double x1, double y1, double x2, double y2, float r, float g, float b, float a, ImPlotDragToolFlags flags) { auto ret = ImPlot::DragRect(id, &x1, &y1, &x2, &y2, {r, g, b, a}, flags); return std::tuple{ret, x1, y1, x2, y2}; }));


    implot.set_function("Annotation",
        sol::overload(
            [](double x, double y, float r, float g, float b, float a, float pix_offset_x, float pix_offset_y, bool clamp) -> void { return ImPlot::Annotation(x, y, {r, g, b, a}, {pix_offset_x, pix_offset_y}, clamp); },
            [](double x, double y, float r, float g, float b, float a, float pix_offset_x, float pix_offset_y, bool clamp, bool round) { ImPlot::Annotation(x, y, {r, g, b, a}, {pix_offset_x, pix_offset_y}, clamp, round); },
            [](double x, double y, float r, float g, float b, float a, float pix_offset_x, float pix_offset_y, bool clamp, const char* text) { ImPlot::Annotation(x, y, {r, g, b, a}, {pix_offset_x, pix_offset_y}, clamp, "%s", text); }));

    implot.set_function("TagX",
        sol::overload(
            [](double x, float r, float g, float b, float a) -> void { return ImPlot::TagX(x, {r, g, b, a}); },
            [](double x, float r, float g, float b, float a, bool round) { ImPlot::TagX(x, {r, g, b, a}, round); },
            [](double x, float r, float g, float b, float a, const char* text) { ImPlot::TagX(x, {r, g, b, a}, "%s", text); }));

    implot.set_function("TagY",
        sol::overload(
            [](double y, float r, float g, float b, float a) -> void { return ImPlot::TagY(y, {r, g, b, a}); },
            [](double y, float r, float g, float b, float a, bool round) { ImPlot::TagY(y, {r, g, b, a}, round); },
            [](double y, float r, float g, float b, float a, const char* text) { ImPlot::TagY(y, {r, g, b, a}, "%s", text); }));


    implot.set_function("SetAxis", sol::resolve<void(ImAxis)>(ImPlot::SetAxis));
    implot.set_function("SetAxes", sol::resolve<void(ImAxis, ImAxis)>(ImPlot::SetAxes));


    implot.set_function("PixelsToPlot",
        sol::overload(
            [](float x, float y) -> std::tuple<double, double> { auto ret = ImPlot::PixelsToPlot(x, y); return std::tuple{ret.x, ret.y}; },
            [](float x, float y, ImAxis x_axis) { auto ret = ImPlot::PixelsToPlot(x, y, x_axis); return std::tuple{ret.x, ret.y}; },
            [](float x, float y, ImAxis x_axis, ImAxis y_axis) { auto ret = ImPlot::PixelsToPlot(x, y, x_axis, y_axis); return std::tuple{ret.x, ret.y}; }));

    implot.set_function("PlotToPixels",
        sol::overload(
            [](double x, double y) -> std::tuple<float, float> { auto ret = ImPlot::PlotToPixels(x, y); return std::tuple{ret.x, ret.y}; },
            [](double x, double y, ImAxis x_axis) { auto ret = ImPlot::PlotToPixels(x, y, x_axis); return std::tuple{ret.x, ret.y}; },
            [](double x, double y, ImAxis x_axis, ImAxis y_axis) { auto ret = ImPlot::PlotToPixels(x, y, x_axis, y_axis); return std::tuple{ret.x, ret.y}; },
            [](ImPlotPoint plt) -> std::tuple<float, float> { auto ret = ImPlot::PlotToPixels(plt); return std::tuple{ret.x, ret.y}; },
            [](ImPlotPoint plt, ImAxis x_axis) { auto ret = ImPlot::PlotToPixels(plt, x_axis); return std::tuple{ret.x, ret.y}; },
            [](ImPlotPoint plt, ImAxis x_axis, ImAxis y_axis) { auto ret = ImPlot::PlotToPixels(plt, x_axis, y_axis); return std::tuple{ret.x, ret.y}; }));


    implot.set_function("GetPlotPos", []() -> std::tuple<float, float> { auto ret = ImPlot::GetPlotPos(); return std::tuple{ret.x, ret.y}; });
    implot.set_function("GetPlotSize", []() -> std::tuple<float, float> { auto ret = ImPlot::GetPlotSize(); return std::tuple{ret.x, ret.y}; });

    implot.set_function("GetPlotMousePos",
        sol::overload(
            []() -> std::tuple<double, double> { auto ret = ImPlot::GetPlotMousePos(); return std::tuple{ret.x, ret.y}; },
            [](ImAxis x_axis) { auto ret = ImPlot::GetPlotMousePos(x_axis); return std::tuple{ret.x, ret.y}; },
            [](ImAxis x_axis, ImAxis y_axis) { auto ret = ImPlot::GetPlotMousePos(x_axis, y_axis); return std::tuple{ret.x, ret.y}; }));

    implot.set_function("GetPlotLimits",
        sol::overload(
            []() -> ImPlotRect { return ImPlot::GetPlotLimits(); },
            [](ImAxis x_axis) { return ImPlot::GetPlotLimits(x_axis); },
            [](ImAxis x_axis, ImAxis y_axis) { return ImPlot::GetPlotLimits(x_axis, y_axis); }));

    implot.set_function("IsPlotHovered", sol::resolve<bool()>(ImPlot::IsPlotHovered));
    implot.set_function("IsAxisHovered", sol::resolve<bool(ImAxis)>(ImPlot::IsAxisHovered));
    implot.set_function("IsSubplotsHovered", sol::resolve<bool()>(ImPlot::IsSubplotsHovered));
    implot.set_function("IsPlotSelected", sol::resolve<bool()>(ImPlot::IsPlotSelected));
    implot.set_function("GetPlotSelection",
        sol::overload(
            []() { return ImPlot::GetPlotSelection(); },
            [](ImAxis x_axis) { return ImPlot::GetPlotSelection(x_axis); },
            [](ImAxis x_axis, ImAxis y_axis) { return ImPlot::GetPlotSelection(x_axis, y_axis); },
            sol::resolve<ImPlotRect(ImAxis, ImAxis)>(ImPlot::GetPlotSelection)));

    implot.set_function("CancelPlotSelection", sol::resolve<void()>(ImPlot::CancelPlotSelection));
    implot.set_function("HideNextItem",
        sol::overload(
            []() { ImPlot::HideNextItem(); },
            [](bool hidden) { ImPlot::HideNextItem(hidden); },
            sol::resolve<void(bool, ImPlotCond)>(ImPlot::HideNextItem)));

    implot.set_function("BeginAlignedPlots",
        sol::overload(
            [](const char* group_id) { return ImPlot::BeginAlignedPlots(group_id); },
            sol::resolve<bool(const char*, bool)>(ImPlot::BeginAlignedPlots)));
    implot.set_function("EndAlignedPlots", sol::resolve<void()>(ImPlot::EndAlignedPlots));

    implot.set_function("BeginLegendPopup",
        sol::overload(
            [](const char* label_id) { return ImPlot::BeginLegendPopup(label_id); },
            sol::resolve<bool(const char*, ImGuiMouseButton)>(ImPlot::BeginLegendPopup)));
    implot.set_function("EndLegendPopup", sol::resolve<void()>(ImPlot::EndLegendPopup));
    implot.set_function("IsLegendEntryHovered", sol::resolve<bool(const char*)>(ImPlot::IsLegendEntryHovered));


    implot.set_function("BeginDragDropTargetPlot", sol::resolve<bool()>(ImPlot::BeginDragDropTargetPlot));
    implot.set_function("BeginDragDropTargetAxis", sol::resolve<bool(ImAxis)>(ImPlot::BeginDragDropTargetAxis));
    implot.set_function("BeginDragDropTargetLegend", sol::resolve<bool()>(ImPlot::BeginDragDropTargetLegend));
    implot.set_function("EndDragDropTarget", sol::resolve<void()>(ImPlot::EndDragDropTarget));


    implot.set_function("PushStyleColor",
        sol::overload(
            [](ImPlotCol idx, float r, float g, float b, float a) { ImPlot::PushStyleColor(idx, {r, g, b, a}); },
            sol::resolve<void(ImPlotCol, ImU32)>(ImPlot::PushStyleColor)));
    implot.set_function("PopStyleColor",
        sol::overload(
            []() { ImPlot::PopStyleColor(); },
            sol::resolve<void(int)>(ImPlot::PopStyleColor)));

    implot.set_function("PushStyleVarFloat", sol::resolve<void(ImPlotStyleVar, float)>(ImPlot::PushStyleVar));
    implot.set_function("PushStyleVarInt", sol::resolve<void(ImPlotStyleVar, int)>(ImPlot::PushStyleVar));
    implot.set_function("PushStyleVarVec2", [](ImPlotStyleVar idx, float x, float y) { ImPlot::PushStyleVar(idx, {x, y}); });
    implot.set_function("PopStyleVar",
        sol::overload(
            []() { ImPlot::PopStyleVar(); },
            sol::resolve<void(int)>(ImPlot::PopStyleVar)));

    implot.set_function("SetNextLineStyle",
        [](std::optional<float> r, std::optional<float> g, std::optional<float> b, std::optional<float> a, std::optional<float> weight) -> void {
            return ImPlot::SetNextLineStyle(from_optional(r, g, b, a), weight.value_or(IMPLOT_AUTO));
        });

    implot.set_function("SetNextFillStyle",
        [](std::optional<float> r, std::optional<float> g, std::optional<float> b, std::optional<float> a, std::optional<float> alpha_mod) -> void {
            return ImPlot::SetNextFillStyle(from_optional(r, g, b, a), alpha_mod.value_or(IMPLOT_AUTO));
        });

    implot.set_function("SetNextMarkerStyle",
        [](std::optional<ImPlotMarker> marker, std::optional<float> size,
            std::optional<float> fill_r, std::optional<float> fill_g, std::optional<float> fill_b, std::optional<float> fill_a,
            std::optional<float> weight,
            std::optional<float> outline_r, std::optional<float> outline_g, std::optional<float> outline_b, std::optional<float> outline_a
        ) -> void
        {
            return ImPlot::SetNextMarkerStyle(
                marker.value_or(IMPLOT_AUTO),
                size.value_or(IMPLOT_AUTO),
                from_optional(fill_r, fill_g, fill_b, fill_a),
                weight.value_or(IMPLOT_AUTO),
                from_optional(outline_r, outline_g, outline_b, outline_a)
            );
        });

    implot.set_function("SetNextErrorBarStyle",
        [](std::optional<float> r, std::optional<float> g, std::optional<float> b, std::optional<float> a, std::optional<float> size, std::optional<float> weight) -> void {
            return ImPlot::SetNextErrorBarStyle(from_optional(r, g, b, a), size.value_or(IMPLOT_AUTO), weight.value_or(IMPLOT_AUTO));
        });

    implot.set_function("GetLastItemColor",
        []() -> std::tuple<float, float, float, float> { auto ret = ImPlot::GetLastItemColor(); return std::tuple{ret.x, ret.y, ret.z, ret.w}; });

    implot.set_function("GetStyleColorName", sol::resolve<const char*(ImPlotCol)>(ImPlot::GetStyleColorName));
    implot.set_function("GetMarkerName", sol::resolve<const char*(ImPlotMarker)>(ImPlot::GetMarkerName));


    implot.set_function("ItemIcon",
        sol::overload(
            sol::resolve<void(ImU32)>(ImPlot::ItemIcon),
            [](float r, float g, float b, float a) { ImPlot::ItemIcon({r, g, b, a}); }));
    implot.set_function("ColormapIcon", sol::resolve<void(ImPlotColormap)>(ImPlot::ColormapIcon));


    implot.set_function("PushPlotClipRect",
        sol::overload(
            []() { ImPlot::PushPlotClipRect(); },
            sol::resolve<void(float)>(ImPlot::PushPlotClipRect)));
    implot.set_function("PopPlotClipRect", sol::resolve<void()>(ImPlot::PopPlotClipRect));

    implot.set_function("ShowStyleSelector", sol::resolve<bool(const char*)>(ImPlot::ShowStyleSelector));
    implot.set_function("ShowColormapSelector", sol::resolve<bool(const char*)>(ImPlot::ShowColormapSelector));
    implot.set_function("ShowInputMapSelector", sol::resolve<bool(const char*)>(ImPlot::ShowInputMapSelector));
    implot.set_function("ShowUserGuide", sol::resolve<void()>(ImPlot::ShowUserGuide));
    implot.set_function("ShowMetricsWindow",
        sol::overload(
            []() -> void { return ImPlot::ShowMetricsWindow(); },
            [](bool open) -> bool { ImPlot::ShowMetricsWindow(&open); return open; }));

    implot.set_function("ShowDemoWindow",
        sol::overload(
            []() -> void { return ImPlot::ShowDemoWindow(); },
            [](bool open) -> bool { ImPlot::ShowDemoWindow(&open); return open; }));

    imgui["implot"] = implot;
}
