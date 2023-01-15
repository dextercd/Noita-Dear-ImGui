#ifndef NOITA_IMGUI_VERSION_NUMBER_HPP
#define NOITA_IMGUI_VERSION_NUMBER_HPP

#include <cassert>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>

#include "noita_dear_imgui_export.h"

struct version_number {
    int major = -1;
    int minor = -1;
    int patch = -1;
    int tweak = -1;

    friend std::weak_ordering operator<=>(const version_number&, const version_number&) = default;

    NOITA_DEAR_IMGUI_EXPORT
    static std::optional<version_number> from_string(std::string_view version_str);

    constexpr version_number zero_fill() const
    {
        version_number ret = *this;
        if (ret.minor == -1) ret.minor = 0;
        if (ret.patch == -1) ret.patch = 0;
        if (ret.tweak == -1) ret.tweak = 0;
        return ret;
    }

    constexpr version_number without_tweak() const
    {
        auto ret = *this;
        ret.tweak = -1;
        return ret;
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
    if (a.tweak >= b.tweak) return true;

    // Unreachable
    assert(false);
    return false;
}

NOITA_DEAR_IMGUI_EXPORT
std::ostream& operator<<(std::ostream& os, const version_number&);

std::string to_string(const version_number&);

#endif // header guard
