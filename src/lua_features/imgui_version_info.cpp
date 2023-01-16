#include <array>

#include <sol/sol.hpp>
#include <imgui.h>

#include <noita_imgui/version_info.hpp>

void add_imgui_version_info(sol::state_view lua, sol::table& imgui)
{
    imgui.set("version_info",
        lua.create_table_with(
            "ndi", lua.create_table_with(
                "parts", sol::as_table(std::array<int, 4>{
                    ndi::version.major,
                    ndi::version.minor,
                    ndi::version.patch,
                    ndi::version.tweak,
                }),
                "str", to_string(ndi::version),
                "git_sha", ndi::git_sha
            ),
            "imgui", lua.create_table_with(
                "str", IMGUI_VERSION,
                "num", IMGUI_VERSION_NUM
            )));
}
