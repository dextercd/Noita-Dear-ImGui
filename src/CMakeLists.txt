include(GenerateExportHeader)

set(public_headers
    include/noita_imgui/add_lua_features.hpp
    include/noita_imgui/version_info.hpp
    include/noita_imgui/version_number.hpp
    include/noita_imgui/imgui_config.hpp
    include/noita_imgui/pause.hpp
)

set(dear_imgui_headers
    ${dearimgui_SOURCE_DIR}/imconfig.h
    ${dearimgui_SOURCE_DIR}/imgui.h
    ${dearimgui_SOURCE_DIR}/imgui_internal.h
    ${dearimgui_SOURCE_DIR}/imstb_rectpack.h
    ${dearimgui_SOURCE_DIR}/imstb_textedit.h
    ${dearimgui_SOURCE_DIR}/imstb_truetype.h
    ${implot_SOURCE_DIR}/implot.h
    ${implot_SOURCE_DIR}/implot_internal.h
)

add_library(noita_dear_imgui SHARED
    main.cpp
    version_number.cpp
    ${VERSION_INFO_CPP}
    style.cpp
    wine_compat.cpp
    version_compat_window.cpp
    pause.cpp

    # Dear ImGui sources
    ${dearimgui_SOURCE_DIR}/imgui.cpp
    ${dearimgui_SOURCE_DIR}/imgui_demo.cpp
    ${dearimgui_SOURCE_DIR}/imgui_draw.cpp
    ${dearimgui_SOURCE_DIR}/imgui_tables.cpp
    ${dearimgui_SOURCE_DIR}/imgui_widgets.cpp
    imgui_impl_sdl2.cpp
    ${dearimgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp

    # ImPlot
    ${implot_SOURCE_DIR}/implot.cpp
    ${implot_SOURCE_DIR}/implot_items.cpp
    ${implot_SOURCE_DIR}/implot_demo.cpp

    # Lua features
    add_lua_features.cpp
    lua_features/imgui_clipboard.cpp
    lua_features/imgui_color_editor.cpp
    lua_features/imgui_combo_box.cpp
    lua_features/imgui_common.cpp
    lua_features/imgui_disable.cpp
    lua_features/imgui_drag_and_drop.cpp
    lua_features/imgui_drag_sliders.cpp
    lua_features/imgui_font.cpp
    lua_features/imgui_gui_io.cpp
    lua_features/imgui_keyboard_input.cpp
    lua_features/imgui_layout.cpp
    lua_features/imgui_list_clipper.cpp
    lua_features/imgui_menu.cpp
    lua_features/imgui_mouse_input.cpp
    lua_features/imgui_param_stacks.cpp
    lua_features/imgui_popup.cpp
    lua_features/imgui_regular_sliders.cpp
    lua_features/imgui_scopes.cpp
    lua_features/imgui_style.cpp
    lua_features/imgui_tables.cpp
    lua_features/imgui_tabs.cpp
    lua_features/imgui_text.cpp
    lua_features/imgui_text_input.cpp
    lua_features/imgui_tooltips.cpp
    lua_features/imgui_trees.cpp
    lua_features/imgui_version_info.cpp
    lua_features/imgui_viewports.cpp
    lua_features/imgui_widget_utils.cpp
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

set_target_properties(noita_dear_imgui PROPERTIES
    PUBLIC_HEADER "${public_headers}"
    ARCHIVE_OUTPUT_NAME_DEBUG "noita_dear_imgui-debug"
)

generate_export_header(noita_dear_imgui)

target_include_directories(noita_dear_imgui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${dearimgui_SOURCE_DIR}>
        $<BUILD_INTERFACE:${implot_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(noita_dear_imgui
    PRIVATE
        LuaJIT_library
        sol2::sol2
        SDL2
        minhook
)

if (MINGW)
    # sol2 include some headers that transitively includes pthread stuff
    find_package(Threads REQUIRED)
    target_link_libraries(noita_dear_imgui PUBLIC Threads::Threads)
endif()


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

    PUBLIC_HEADER
        COMPONENT NoitaImGui_Native
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/noita_imgui"

    ARCHIVE
        COMPONENT NoitaImGui_Native
        DESTINATION "NoitaDearImGui/native/lib"
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/noita_dear_imgui_export.h
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT NoitaImGui_Native
)

install(TARGETS noita_dear_imgui
    CONFIGURATIONS Release
    RUNTIME
        COMPONENT NoitaImGui
        DESTINATION "NoitaDearImGui"
)

install(TARGETS noita_dear_imgui
    CONFIGURATIONS Debug
    RUNTIME
        COMPONENT NoitaImGui
        DESTINATION "NoitaDearImGui/Debug"
)

if (CMAKE_CXX_LINKER_SUPPORTS_PDB)
    install(FILES $<TARGET_PDB_FILE:noita_dear_imgui>
        DESTINATION "NoitaDearImGui/Debug"
        CONFIGURATIONS Debug RelWithDebInfo
        COMPONENT NoitaImGui_Native
    )
endif()

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
