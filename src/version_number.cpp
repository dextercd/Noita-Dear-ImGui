#include "version_number.hpp"
#include "noita_dear_imgui_export.h"

NOITA_DEAR_IMGUI_EXPORT
std::ostream& operator<<(std::ostream& os, const version_number& version)
{
    if (version.major != -1) os << version.major; else goto do_suffix;
    if (version.minor != -1) os << '.' << version.minor; else goto do_suffix;
    if (version.patch != -1) os << '.' << version.patch; else goto do_suffix;
    if (version.tweak != -1) os << '.' << version.tweak; else goto do_suffix;

do_suffix:
    if (!version.suffix.empty())
        os << '-' << version.suffix;

    return os;
}
