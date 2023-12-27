add_library(test_lib INTERFACE)
target_link_libraries(test_lib INTERFACE noita_dear_imgui Catch2::Catch2WithMain)
target_include_directories(test_lib INTERFACE ..)

add_executable(noita_imgui_test
    test_version.cpp
)

target_link_libraries(noita_imgui_test PRIVATE test_lib)

add_test(NAME noita_imgui_test COMMAND noita_imgui_test)

set(noita_imgui_lib_dir "$<SHELL_PATH:$<TARGET_FILE_DIR:noita_dear_imgui>>")
set(noita_imgui_sdl_lib_dir "$<SHELL_PATH:$<TARGET_FILE_DIR:SDL2>>")
set(noita_imgui_lua_lib_dir "$<SHELL_PATH:${LUA_LIBRARIES}>")

if (CMAKE_HOST_WIN32)
    set_property(TEST noita_imgui_test APPEND PROPERTY
        ENVIRONMENT_MODIFICATION
            PATH=path_list_prepend:${noita_imgui_lib_dir}
            PATH=path_list_prepend:${noita_imgui_sdl_lib_dir}
            PATH=path_list_prepend:${noita_imgui_lua_lib_dir}
    )
else()
    set_property(TEST noita_imgui_test APPEND PROPERTY
        ENVIRONMENT_MODIFICATION
            "WINEPATH=string_prepend:${noita_imgui_lib_dir}\;"
            "WINEPATH=string_prepend:${noita_imgui_sdl_lib_dir}\;"
            "WINEPATH=string_prepend:${noita_imgui_lua_lib_dir}\;"
    )
endif()
