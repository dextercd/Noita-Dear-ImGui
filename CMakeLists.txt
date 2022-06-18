cmake_minimum_required(VERSION 3.22)

project(NoitaDearImGui)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
include(ExternalProject)
include(GenerateExportHeader)

find_program(CLANGXX clang++ REQUIRED)

FetchContent_Declare(MinHook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG 4a455528f61b5a375b1f9d44e7d296d47f18bb18
)

FetchContent_MakeAvailable(MinHook)

FetchContent_Declare(SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.0.7-VC.zip
    URL_HASH SHA224=2c64cce76e917525e6096481ee7f46b0c999838ae65405e9af8df367
)

FetchContent_MakeAvailable(SDL2)

file(COPY_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/fixup/SDL_syswm.h
    ${sdl2_SOURCE_DIR}/include/SDL_syswm.h
    ONLY_IF_DIFFERENT)

add_library(SDL2 SHARED IMPORTED)
set_target_properties(SDL2 PROPERTIES
    IMPORTED_LOCATION ${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll
    IMPORTED_IMPLIB   ${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib
)

target_include_directories(SDL2
    INTERFACE
        ${sdl2_SOURCE_DIR}/include
)


FetchContent_Declare(DearImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG 07efd7cc2053099c2f29e65b33e03d56a4b8d53c
)

FetchContent_GetProperties(DearImGui)
if (NOT dearimgui_POPULATED)
    FetchContent_Populate(DearImGui)
endif()

set(IMGUI_AST_DUMP "${CMAKE_CURRENT_BINARY_DIR}/imgui_ast_dump.json")

add_custom_command(
    OUTPUT ${IMGUI_AST_DUMP}
    COMMAND ${CLANGXX} -c
        -fdelayed-template-parsing
        -fms-extensions
        -fms-compatibility
        -Xclang
        -ast-dump=json
        ${dearimgui_SOURCE_DIR}/imgui.h
        -ferror-limit=1000
        >${IMGUI_AST_DUMP}
    || cd .
)

add_custom_target(imgui_ast_dump DEPENDS ${IMGUI_AST_DUMP})


add_library(DearImGui STATIC
    ${dearimgui_SOURCE_DIR}/imgui.cpp
    ${dearimgui_SOURCE_DIR}/imgui_demo.cpp
    ${dearimgui_SOURCE_DIR}/imgui_draw.cpp
    ${dearimgui_SOURCE_DIR}/imgui_tables.cpp
    ${dearimgui_SOURCE_DIR}/imgui_widgets.cpp
    ${dearimgui_SOURCE_DIR}/backends/imgui_impl_sdl.cpp
    ${dearimgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(DearImGui
    PUBLIC
        ${dearimgui_SOURCE_DIR}
)

target_compile_definitions(DearImGui
    PUBLIC
        IMGUI_DISABLE_OBSOLETE_KEYIO
        IMGUI_DISABLE_OBSOLETE_FUNCTIONS
)

target_link_libraries(DearImGui PUBLIC SDL2)

ExternalProject_Add(LuaJIT
    URL https://luajit.org/download/LuaJIT-2.0.4.zip
    URL_HASH SHA224=163def4ec3ad502702760c703bb81da7932573a6f4b2ff482d04ccb6
    BUILD_IN_SOURCE ON
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E chdir "<SOURCE_DIR>/src" "msvcbuild.bat"
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_if_different
        <SOURCE_DIR>/src/luajit.exe
        <SOURCE_DIR>/src/lua51.dll
        <SOURCE_DIR>/src/lua51.lib
        <INSTALL_DIR>

    BUILD_BYPRODUCTS
        <SOURCE_DIR>/src/luajit.exe
        <SOURCE_DIR>/src/lua51.dll
        <SOURCE_DIR>/src/lua51.lib
)

ExternalProject_Add_Step(LuaJIT install-lua-files
    COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/src/jit <INSTALL_DIR>/lua/jit
    DEPENDEES configure
)

ExternalProject_Get_Property(LuaJIT INSTALL_DIR SOURCE_DIR)

add_library(LuaJIT_library SHARED IMPORTED)
set_target_properties(LuaJIT_library PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/lua51.dll
    IMPORTED_IMPLIB   ${INSTALL_DIR}/lua51.lib
)

target_include_directories(LuaJIT_library
    INTERFACE
        ${SOURCE_DIR}/src
)

add_executable(LuaJIT_exe IMPORTED)
set_target_properties(LuaJIT_exe PROPERTIES
    IMPORTED_LOCATION ${INSTALL_DIR}/luajit.exe
)


FetchContent_Declare(sol
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG 2198d9374d260f168d53b6248e49068a6307227d
)

FetchContent_MakeAvailable(sol)

add_subdirectory(src)

install(TARGETS noita_dear_imgui DESTINATION "DearImGui" COMPONENT NoitaImGui)
install(DIRECTORY DearImGui DESTINATION "." COMPONENT NoitaImGui)
