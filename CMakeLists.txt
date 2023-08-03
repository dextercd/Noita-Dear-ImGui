cmake_minimum_required(VERSION 3.22)

project(NoitaDearImGui
    VERSION 1.11.1.0
    LANGUAGES CXX C
    HOMEPAGE_URL "https://github.com/dextercd/Noita-Dear-ImGui"
)

set(CMAKE_CXX_STANDARD 17)

# Don't add lib suffix when crosscompiling from Linux
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")

# Default to 'DOWNLOAD_EXTRACT_TIMESTAMP TRUE' when available
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(CTest)
include(FetchContent)
include(ExternalProject)

FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG 605a34765aa5d5ecbf476b4598a862ada971b0cc  # v3.0.1
)

FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(MinHook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG 4a455528f61b5a375b1f9d44e7d296d47f18bb18)
FetchContent_MakeAvailable(MinHook)


FetchContent_Declare(SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.0.7-VC.zip
    URL_HASH SHA224=2c64cce76e917525e6096481ee7f46b0c999838ae65405e9af8df367)
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
    GIT_TAG 95412ad3a5c03f63eba116a5435302fec52e99e5
)

FetchContent_GetProperties(DearImGui)
if (NOT dearimgui_POPULATED)
    FetchContent_Populate(DearImGui)
endif()


FetchContent_Declare(ImPlot
    GIT_REPOSITORY https://github.com/epezent/implot.git
    GIT_TAG cc5e1daa5c7f2335a9460ae79c829011dc5cef2d
)
FetchContent_GetProperties(ImPlot)
if (NOT implot_POPULATED)
    FetchContent_Populate(ImPlot)
endif()

set(LUAJIT_OUTPUT luajit.exe lua51.dll)
if (MSVC)
    set(LUAJIT_BUILD ${CMAKE_COMMAND} -E chdir "<SOURCE_DIR>/src" "msvcbuild.bat")
    list(APPEND LUAJIT_OUTPUT lua51.lib)
else()
    # Not MSVC so try the Makefile instead
    find_program(MAKE_EXECUTABLE NAMES gmake make)
    set(LUAJIT_BUILD
        ${MAKE_EXECUTABLE}
            HOST_CC=cc
            HOST_CFLAGS=-m32
            HOST_LDFLAGS=-m32
            "CC=${CMAKE_C_COMPILER}"
            "TARGET_CFLAGS=${CMAKE_C_FLAGS}"
            "TARGET_LDFLAGS=${CMAKE_EXE_LINKER_FLAGS}"
            "TARGET_SHLDFLAGS=${CMAKE_SHARED_LINKER_FLAGS}"
            TARGET_SYS=Windows
    )
endif()

set(LUAJIT_SOURCE_PATHS)
set(LUAJIT_INSTALL_PATHS)
foreach(OUT IN LISTS LUAJIT_OUTPUT)
    list(APPEND LUAJIT_SOURCE_PATHS "<SOURCE_DIR>/src/${OUT}")
    list(APPEND LUAJIT_INSTALL_PATHS "<INSTALL_DIR>/${OUT}")
endforeach()

ExternalProject_Add(LuaJIT
    URL https://luajit.org/download/LuaJIT-2.0.4.zip
    URL_HASH SHA224=163def4ec3ad502702760c703bb81da7932573a6f4b2ff482d04ccb6
    BUILD_IN_SOURCE ON
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/LuaJIT

    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${LUAJIT_BUILD}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LUAJIT_SOURCE_PATHS}
        <INSTALL_DIR>

    INSTALL_COMMAND ""

    BUILD_BYPRODUCTS
        ${LUAJIT_INSTALL_PATHS}
)

ExternalProject_Add_Step(LuaJIT install-lua-files
    COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/src/jit <INSTALL_DIR>/lua/jit
    DEPENDEES configure
)

ExternalProject_Get_Property(LuaJIT INSTALL_DIR SOURCE_DIR)

add_library(LuaJIT_library SHARED IMPORTED)

if (lua51.lib IN_LIST LUAJIT_OUTPUT)
    set_target_properties(LuaJIT_library PROPERTIES
        IMPORTED_LOCATION ${INSTALL_DIR}/lua51.dll
        IMPORTED_IMPLIB   ${INSTALL_DIR}/lua51.lib
    )
else()
    set_target_properties(LuaJIT_library PROPERTIES
        IMPORTED_LOCATION ${INSTALL_DIR}/lua51.dll
        IMPORTED_IMPLIB   ${INSTALL_DIR}/lua51.dll
    )
endif()

# Bit of a hack, include dir won't exist yet after the generate stage but CMake
# requires it to be.
file(MAKE_DIRECTORY ${SOURCE_DIR}/src)
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
    GIT_TAG 19898d8d3e6c3def33625082343428be1bb9387b
)

FetchContent_MakeAvailable(sol)

set(VERSION_INFO_TXT "${CMAKE_CURRENT_BINARY_DIR}/version_info.txt")
set(VERSION_INFO_CPP "${CMAKE_CURRENT_BINARY_DIR}/version_info.cpp")

find_program(GIT_PROGRAM git)

set(git_file_list
    version_info.txt.in ${VERSION_INFO_TXT}
    version_info.cpp.in ${VERSION_INFO_CPP}
)

add_custom_target(version_info_files ALL
    VERBATIM
    COMMAND cmake
        -D GIT_PROGRAM=${GIT_PROGRAM}
        -D "FILES=${git_file_list}"
        -D "PROJECT_HOMEPAGE_URL=${NoitaDearImGui_HOMEPAGE_URL}"
        -D "PROJECT_VERSION=${NoitaDearImGui_VERSION}"
        -D "PROJECT_VERSION_MAJOR=${NoitaDearImGui_VERSION_MAJOR}"
        -D "PROJECT_VERSION_MINOR=${NoitaDearImGui_VERSION_MINOR}"
        -D "PROJECT_VERSION_PATCH=${NoitaDearImGui_VERSION_PATCH}"
        -D "PROJECT_VERSION_TWEAK=${NoitaDearImGui_VERSION_TWEAK}"
        -P cmake/write_git_info.cmake

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    BYPRODUCTS ${VERSION_INFO_TXT} ${VERSION_INFO_CPP}
)

set(CMAKE_INSTALL_INCLUDEDIR "NoitaDearImGui/native/include")

add_subdirectory(src)

set(NDI_SUBPROJECT TRUE)
add_subdirectory(ExampleNative)

install(DIRECTORY NoitaDearImGui DESTINATION "." COMPONENT NoitaImGui)
install(FILES ${VERSION_INFO_TXT} DESTINATION "NoitaDearImGui" COMPONENT NoitaImGui)

install(DIRECTORY ExampleMod/ DESTINATION "NoitaDearImGuiExampleMod" COMPONENT NoitaImGui_Example)

add_subdirectory(packaging)
