add_library(noita_dear_imgui MODULE
    main.cpp
    add_lua_features.cpp

    lua_features/imgui_gui_io.cpp
    lua_features/imgui_windows.cpp
    lua_features/imgui_text.cpp
)

generate_export_header(noita_dear_imgui)

target_include_directories(noita_dear_imgui PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(noita_dear_imgui
    PRIVATE
        LuaJIT_library
        sol2::sol2
        DearImGui
        SDL2
        minhook
)

target_precompile_headers(noita_dear_imgui PRIVATE
    <sol/sol.hpp>
    <imgui.h>
)
