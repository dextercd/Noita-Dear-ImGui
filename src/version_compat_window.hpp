#ifndef NOITA_IMGUI_VERSION_COMPAT_WINDOW_HPP
#define NOITA_IMGUI_VERSION_COMPAT_WINDOW_HPP

#include <string>

enum incompatibility_reason {
    cant_parse_version,
    version_mismatch,
};

void show_version_compat_window();
void report_incompatibility(std::string mod_name, std::string version, incompatibility_reason reason);

#endif // header guard
