#include "version_number.hpp"
#include "noita_dear_imgui_export.h"

NOITA_DEAR_IMGUI_EXPORT
std::optional<version_number> version_number::from_string(
    std::string_view version_str)
{
    version_number ver{};

    auto const version_end = version_str.data() + version_str.size();

    int component_nr = 0;
    for (const auto crange : std::views::split(version_str, sep)) {
        auto component = std::string_view(crange.begin(), crange.end());
        auto component_end = component.data() + component.size();

        int* assigning_component = nullptr;
        if (component_nr == 0) assigning_component = &ver.major;
        if (component_nr == 1) assigning_component = &ver.minor;
        if (component_nr == 2) assigning_component = &ver.patch;
        if (component_nr == 3) assigning_component = &ver.tweak;

        // Too many parts in the version string
        if (assigning_component == nullptr)
            return std::nullopt;

        auto [parse_end, ec] = std::from_chars(
            component.data(), component.data() + component.size(),
            *assigning_component
        );

        // Couldn't parse the number
        if (ec != std::errc{})
            return std::nullopt;

        // Negative version component
        if (*assigning_component < 0)
            return std::nullopt;

        // Junk at the end of the number
        if (parse_end != component_end)
            return std::nullopt;

        // Nothing after the digits, continue with next component
        ++component_nr;
    }

    if (component_nr == 0)
        return std::nullopt;

    return ver;
}

NOITA_DEAR_IMGUI_EXPORT
std::ostream& operator<<(std::ostream& os, const version_number& version)
{
    if (version.major != -1) os << version.major; else goto end;
    if (version.minor != -1) os << '.' << version.minor; else goto end;
    if (version.patch != -1) os << '.' << version.patch; else goto end;
    if (version.tweak != -1) os << '.' << version.tweak; else goto end;

end:
    return os;
}
