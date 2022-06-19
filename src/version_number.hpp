#include <cassert>
#include <charconv>
#include <iosfwd>
#include <optional>
#include <ranges>
#include <string>

#include "noita_dear_imgui_export.h"

struct version_number {
    constexpr static std::string_view sep = ".";

    int major = -1;
    int minor = -1;
    int patch = -1;
    int tweak = -1;
    std::string suffix;

    friend std::weak_ordering operator<=>(const version_number&, const version_number&) = default;

    constexpr static std::optional<version_number> from_string(
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

            if (parse_end != component_end) {
                // Something after the digits, see if it's a '-suffix'

                // The part we parse is always inside the version_str and we
                // know that parse_end points at more content.
                assert(parse_end < version_end);

                if (*parse_end != '-')
                    return std::nullopt;

                ver.suffix = std::string{parse_end + 1, version_end};
                return ver;

            }

            // Nothing after the digits, continue with next component
            ++component_nr;
        }

        if (component_nr == 0)
            return std::nullopt;

        return ver;
    }
};

constexpr bool version_compatible(const version_number& a, const version_number& b)
{
    if (a.major != b.major) return false;

    if (a.minor == -1) return true;
    if (a.minor < b.minor) return false;
    if (a.minor > b.minor) return true;

    if (a.patch == -1) return true;
    if (a.patch < b.patch) return false;
    if (a.patch > b.patch) return true;

    if (a.tweak == -1) return true;
    if (a.tweak < b.tweak) return false;
    if (a.tweak > b.tweak) return true;

    if (a.suffix.empty() || b.suffix.empty()) return true;
    return a.suffix == b.suffix;
}

NOITA_DEAR_IMGUI_EXPORT
std::ostream& operator<<(std::ostream& os, const version_number&);
