#ifndef NOITA_DEAR_IMGUI_CONTAINER_HPP
#define NOITA_DEAR_IMGUI_CONTAINER_HPP

#include <sol/sol.hpp>

#include <vector>

struct vecfloat {
    std::vector<double> constructed;
    const std::vector<double>* ref;

    const std::vector<double>& get() const
    {
        if (ref)
            return *ref;

        return constructed;
    }

    const double* data() const
    {
        return get().data();
    }

    const std::size_t size() const
    {
        return get().size();
    }
};

template <typename Handler>
bool sol_lua_check(sol::types<vecfloat>, lua_State* L, int index, Handler&& handler, sol::stack::record& tracking) {
    bool success = sol::stack::check<const std::vector<double>*>(L, index, handler)
                || sol::stack::check<std::vector<double>>(L, index, handler);
    tracking.use(1);
    return success;
}

inline vecfloat sol_lua_get(sol::types<vecfloat>, lua_State* L, int index, sol::stack::record& tracking) {
    tracking.use(1);

    if (sol::stack::check<const std::vector<double>*>(L, index)) {
        auto vecptr = sol::stack::get<const std::vector<double>*>(L, index);
        return vecfloat{.ref = vecptr};
    }

    return vecfloat{
        .constructed = sol::stack::get<std::vector<double>>(L, index),
    };
}

#endif // Header guard
