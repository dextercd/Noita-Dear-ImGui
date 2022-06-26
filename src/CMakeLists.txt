include(GenerateExportHeader)

set(public_headers
    include/noita_imgui/add_lua_features.hpp
    include/noita_imgui/version_info.hpp
    include/noita_imgui/version_number.hpp
    include/noita_imgui/imgui_config.hpp
)

set(dear_imgui_headers
    ${dearimgui_SOURCE_DIR}/imconfig.h
    ${dearimgui_SOURCE_DIR}/imgui.h
    ${dearimgui_SOURCE_DIR}/imgui_internal.h
    ${dearimgui_SOURCE_DIR}/imstb_rectpack.h
    ${dearimgui_SOURCE_DIR}/imstb_textedit.h
    ${dearimgui_SOURCE_DIR}/imstb_truetype.h
)

add_library(noita_dear_imgui SHARED
    main.cpp
    version_number.cpp
    ${VERSION_INFO_CPP}
    style.cpp
    wine_compat.cpp

    # Dear ImGui sources
    ${dearimgui_SOURCE_DIR}/imgui.cpp
    ${dearimgui_SOURCE_DIR}/imgui_demo.cpp
    ${dearimgui_SOURCE_DIR}/imgui_draw.cpp
    ${dearimgui_SOURCE_DIR}/imgui_tables.cpp
    ${dearimgui_SOURCE_DIR}/imgui_widgets.cpp
    imgui_impl_sdl.cpp
    ${dearimgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp

    # Lua features
    add_lua_features.cpp
    lua_features/imgui_clipboard.cpp
    lua_features/imgui_color_editor.cpp
    lua_features/imgui_combo_box.cpp
    lua_features/imgui_common.cpp
    lua_features/imgui_drag_sliders.cpp
    lua_features/imgui_gui_io.cpp
    lua_features/imgui_keyboard_input.cpp
    lua_features/imgui_layout.cpp
    lua_features/imgui_menu.cpp
    lua_features/imgui_mouse_input.cpp
    lua_features/imgui_regular_sliders.cpp
    lua_features/imgui_scopes.cpp
    lua_features/imgui_text.cpp
    lua_features/imgui_trees.cpp
    lua_features/imgui_widgets_main.cpp
    lua_features/imgui_windows.cpp

    ${public_headers}
    ${dear_imgui_headers}
)
add_library(NoitaDearImGui::noita_dear_imgui ALIAS noita_dear_imgui)

target_compile_definitions(noita_dear_imgui
    PUBLIC
        IMGUI_DISABLE_OBSOLETE_KEYIO
        IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        IMGUI_USER_CONFIG=<noita_imgui/imgui_config.hpp>
)

target_compile_features(noita_dear_imgui PUBLIC cxx_std_20)

set_target_properties(noita_dear_imgui PROPERTIES
    PUBLIC_HEADER "${public_headers}"
)

generate_export_header(noita_dear_imgui)

target_include_directories(noita_dear_imgui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${dearimgui_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(noita_dear_imgui
    PRIVATE
        LuaJIT_library
        sol2::sol2
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
        DESTINATION "NoitaDearImGui"

    ARCHIVE
        COMPONENT NoitaImGui_Native
        DESTINATION "NoitaDearImGui/native/lib"

    PUBLIC_HEADER
        COMPONENT NoitaImGui_Native
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/noita_imgui"
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/noita_dear_imgui_export.h
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT NoitaImGui_Native
)

install(FILES ${dear_imgui_headers}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT NoitaImGui_Native
)

install(EXPORT NoitaDearImGui
    COMPONENT NoitaImGui_Native
    DESTINATION "NoitaDearImGui/cmake"
    NAMESPACE NoitaDearImGui::
    FILE NoitaDearImGuiConfig.cmake
)
