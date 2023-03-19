# Based on: https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   clang)
set(CMAKE_CXX_COMPILER clang++)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)

# So that tests and codegen programs can be run
set(CMAKE_CROSSCOMPILING_EMULATOR wine)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(COMMON_FLAGS "--sysroot /usr/i686-w64-mingw32 -I /usr/i686-w64-mingw32/include/c++/12.2.0/ -I /usr/i686-w64-mingw32/include/c++/12.2.0/i686-w64-mingw32")

set(COMPILE_FLAGS "-static -target i686-pc-windows-gnu -fuse-ld=lld -fms-extensions -DCOMPAT53_HAVE_STRERROR_R=0 ${COMMON_FLAGS}")

set(CMAKE_C_FLAGS_INIT "${COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${COMPILE_FLAGS}")

set(LINK_FLAGS "-target i686-pc-windows-gnu -fuse-ld=lld -L /usr/lib/gcc/i686-w64-mingw32/12.2.0 -lpthread ${COMMON_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${LINK_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${LINK_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${LINK_FLAGS}")
