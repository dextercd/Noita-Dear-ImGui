include(GenerateExportHeader)

set(public_headers
    include/noita_imgui/add_lua_features.hpp
    include/noita_imgui/version_info.hpp
    include/noita_imgui/version_number.hpp
)

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
    ${public_headers}
)

set_target_properties(noita_dear_imgui PROPERTIES
    PUBLIC_HEADER "${public_headers}"
)

generate_export_header(noita_dear_imgui)

target_include_directories(noita_dear_imgui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
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

install(TARGETS noita_dear_imgui
    EXPORT NoitaDearImGui
    RUNTIME
        COMPONENT NoitaImGui
        DESTINATION "DearImGui"

    ARCHIVE
        COMPONENT NoitaImGui_Native
        DESTINATION "DearImGui/native/lib"

    PUBLIC_HEADER
        COMPONENT NoitaImGui_Native
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/noita_imgui"
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/noita_dear_imgui_export.h
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT NoitaImGui_Native
)
