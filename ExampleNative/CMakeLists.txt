cmake_minimum_required(VERSION 3.21)

project(native_test)

# The NDI_SUBPROJECT if is only there because we want to be able to compile this
# as a subproject.  Normally you would only have the find_package.

if (NOT NDI_SUBPROJECT)
    # Find the NoitaDearImGui package
    find_package(NoitaDearImGui REQUIRED)
endif()

add_library(native_test MODULE
    main.cpp)

target_link_libraries(native_test PUBLIC NoitaDearImGui::noita_dear_imgui)

install(TARGETS native_test
    DESTINATION "NoitaDearImGuiNativeExample"
    COMPONENT NoitaImGui_Example
)

install(
    DIRECTORY NoitaDearImGuiNativeExample
    DESTINATION "."
    COMPONENT NoitaImGui_Example
)
