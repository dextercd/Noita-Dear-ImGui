add_library(noita_dear_imgui SHARED
    main.cpp
    add_lua_features.cpp
    version_number.cpp
    ${VERSION_INFO_CPP}
    lua_features/imgui_gui_io.cpp
    lua_features/imgui_windows.cpp
    lua_features/imgui_text.cpp
    lua_features/imgui_menu.cpp
    lua_features/imgui_widgets_main.cpp
)

generate_export_header(noita_dear_imgui)

target_include_directories(noita_dear_imgui
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(noita_dear_imgui
    PRIVATE
        LuaJIT_library
        sol2::sol2
        DearImGui
        SDL2
        minhook
)

target_precompile_headers(noita_dear_imgui PRIVATE
    <tuple>
    <sol/sol.hpp>
    <imgui.h>
)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
