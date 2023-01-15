#!/bin/bash

project_path=$PWD

if [ ! -d linux-build ]; then
    mkdir linux-build
    pushd linux-build

    cmake "$project_path" \
        -G 'Ninja Multi-Config' \
        -DCMAKE_INSTALL_PREFIX="$HOME/.local/share/Steam/steamapps/common/Noita/mods" \
        -DCMAKE_CXX_FLAGS="-static" \
        -DCMAKE_TOOLCHAIN_FILE="$project_path/TC-mingw.cmake"

    popd
fi

cmake --build linux-build --config Release &&
cmake --build linux-build --config Debug &&
cmake --install linux-build --component NoitaImGui --config Release &&
cmake --install linux-build --component NoitaImGui_Example --config Release &&
cmake --install linux-build --component NoitaImGui_Native --config Release &&
cmake --install linux-build --component NoitaImGui --config Debug &&
cmake --install linux-build --component NoitaImGui_Native --config Debug
