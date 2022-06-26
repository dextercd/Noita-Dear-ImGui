#ifndef NOITA_IMGUI_VERSION_INFO_HPP
#define NOITA_IMGUI_VERSION_INFO_HPP

#include <string_view>

#include "noita_dear_imgui_export.h"
#include "version_number.hpp"

namespace ndi {

NOITA_DEAR_IMGUI_EXPORT
extern constinit const std::string_view git_sha;

NOITA_DEAR_IMGUI_EXPORT
extern constinit const version_number version;

} // namespace ndi

#endif // header guard
