#include <imgui.h>
#include <vector>

#include <noita_imgui/version_info.hpp>
#include "version_compat_window.hpp"

struct incompatibility_report {
    std::string mod_name;
    std::string version;
    incompatibility_reason reason;
};

namespace {
bool dismissed = false;
bool open = false;

std::vector<incompatibility_report> reports;
}

void report_incompatibility(std::string mod_name, std::string version, incompatibility_reason reason)
{
    if (mod_name == "")
        mod_name = "<no name given>";

    reports.push_back(incompatibility_report{std::move(mod_name), std::move(version), reason});
    if (!dismissed)
        open = true;
}

const char* to_cstring(incompatibility_reason reason)
{
    switch (reason) {
        case incompatibility_reason::cant_parse_version:
            return "Didn't understand version string";

        case incompatibility_reason::version_mismatch:
            return "Version mismatch";

        default:
            return "Unknown";
    }
}

void show_version_compat_window()
{
    if (!open)
        return;

    ImGui::SetNextWindowSize(ImVec2(650, 400), ImGuiCond_Once);
    if (!ImGui::Begin("NoitaDearImGui version incompatible", &open)) {
        ImGui::End();

        if (!open)
            dismissed = true;

        return;
    }

    std::string version_text = "Installed version of NoitaDearImGui: ";
    version_text += to_string(ndi::version.without_tweak());
    ImGui::TextWrapped("%s", version_text.c_str());

    ImGui::TextWrapped("%s",
        "One or more mods are not compatible with this version of "
        "NoitaDearImGui. See the table below for more details:"
    );

    if (ImGui::BeginTable("mod_list", 3)) {
        ImGui::TableSetupColumn("Mod name");
        ImGui::TableSetupColumn("Requested Version");
        ImGui::TableSetupColumn("Issue");
        ImGui::TableHeadersRow();

        for (auto& report : reports) {
            ImGui::TableNextColumn();
            ImGui::Text("%s", report.mod_name.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%s", report.version.c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%s", to_cstring(report.reason));
        }

        ImGui::EndTable();
    }

    ImGui::Spacing();
    ImGui::TextWrapped("%s",
        "If a newer version of NoitaDearImGui is available, you should "
        "consider installing it. The mods in the table above may misbehave due "
        "to a version mismatch."
    );
    ImGui::TextWrapped("%s",
        "You should also check if a newer version of any of the mods in the "
        "table above is available."
    );

    if (!open)
        dismissed = true;

    ImGui::End();
}
