#include <vector>

#include <sol/sol.hpp>
#include <imgui.h>

#include "container.hpp"

void add_container(sol::table& imgui)
{
    imgui.set_function("as_vector_float", [](vecfloat vec) { return vec.get(); });
}
