#include <iostream>
#include <noita_imgui/version_info.hpp>
#include <imgui.h>
#include <implot.h>

bool should_show_demo_window = true;

extern "C"
__declspec(dllexport)
void show_demo_window()
{
    if (should_show_demo_window)
        ImGui::ShowDemoWindow(&should_show_demo_window);

    ImPlot::ShowDemoWindow();
}
