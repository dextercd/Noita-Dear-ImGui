cmake_minimum_required(VERSION 3.22)

project(NoitaDearImGui
    VERSION 1.16.1.0
    LANGUAGES CXX C
    HOMEPAGE_URL "https://github.com/dextercd/Noita-Dear-ImGui"
)

set(CMAKE_CXX_STANDARD 20)

# Don't add lib suffix when crosscompiling from Linux
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)

# Default to 'DOWNLOAD_EXTRACT_TIMESTAMP TRUE' when available
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(CTest)
include(FetchContent)
include(ExternalProject)

FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG 53d0d913a422d356b23dd927547febdf69ee9081  # v3.5.0
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
    GIT_TAG 01b99a974dee45181a8fecc70dfb5360852fdff7
)

FetchContent_GetProperties(DearImGui)
if (NOT dearimgui_POPULATED)
    FetchContent_Populate(DearImGui)
endif()


FetchContent_Declare(ImPlot
    GIT_REPOSITORY https://github.com/epezent/implot.git
    GIT_TAG 1f7a8c0314d838a76695bccebe0f66864f507bc0
)
FetchContent_GetProperties(ImPlot)
if (NOT implot_POPULATED)
    FetchContent_Populate(ImPlot)
endif()


# Needed for MINGW to find the LuaJIT dll
if (MINGW)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll ${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

find_package(Lua REQUIRED)


FetchContent_Declare(sol
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG 19898d8d3e6c3def33625082343428be1bb9387b
)

FetchContent_MakeAvailable(sol)


FetchContent_Declare(tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
    GIT_TAG e05956094c27117f989d22f25b75633123d72a83
)

FetchContent_MakeAvailable(tinyxml2)


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
install(FILES imguidoc/imgui_definitions.lua
    DESTINATION NoitaDearImGui/imguidoc
    COMPONENT NoitaImGui
)

add_subdirectory(packaging)
