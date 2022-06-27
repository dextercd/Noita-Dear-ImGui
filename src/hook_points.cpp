#include <optional>

#include <LIEF/PE.hpp>

#include "hook_points.hpp"

void* get_hook_point(const LIEF::PE::Binary& binary, const LIEF::PE::ImportEntry& entry)
{
    auto running_iat_addr = binary.optional_header().imagebase() + entry.iat_address();
    return *reinterpret_cast<void**>(running_iat_addr);
}

std::optional<hook_points> get_hook_points_for_exe(const char* path)
{
    hook_points points{};

    auto binary = LIEF::PE::Parser::parse(path);
    if (!binary)
        return std::nullopt;

    for (const auto& import : binary->imports()) {
        if (import.name() == "SDL2.dll") {
            for (const auto& entry : import.entries()) {
                if (entry.name() == "SDL_PollEvent") {
                    points.sdl_pollevent = get_hook_point(*binary, entry);
                } else if (entry.name() == "SDL_GL_SwapWindow") {
                    points.sdl_gl_swapwindow = get_hook_point(*binary, entry);
                }
            }
        }

        if (import.name() == "lua51.dll") {
            for (const auto& entry : import.entries()) {
                if (entry.name() == "luaL_newstate") {
                    points.lual_newstate = get_hook_point(*binary, entry);
                }
            }
        }
    }

    if (!points.complete())
        return std::nullopt;

    return points;
}
