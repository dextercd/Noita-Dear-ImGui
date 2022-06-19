#include "version_number.hpp"
#include "noita_dear_imgui_export.h"

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
