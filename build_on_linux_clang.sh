#!/bin/bash

project_path=$PWD

if [ ! -d clang-build ]; then
    mkdir clang-build
    pushd clang-build

    cmake "$project_path" \
        -G 'Ninja Multi-Config' \
        -DCMAKE_INSTALL_PREFIX="$HOME/.local/share/Steam/steamapps/common/Noita/mods" \
        -DCMAKE_TOOLCHAIN_FILE="$project_path/TC-clang.cmake"

    popd
fi

cmake --build clang-build --config Release &&
cmake --build clang-build --config Debug &&
cmake --install clang-build --component NoitaImGui --config Release &&
cmake --install clang-build --component NoitaImGui_Example --config Release &&
cmake --install clang-build --component NoitaImGui_Native --config Release &&
cmake --install clang-build --component NoitaImGui --config Debug &&
cmake --install clang-build --component NoitaImGui_Native --config Debug
