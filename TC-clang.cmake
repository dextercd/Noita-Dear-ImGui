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
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)

set(TC_COMMON_FLAGS "")
set(TC_COMPILE_FLAGS "")
set(TC_LINK_FLAGS "")

# We're building for 32 bit Windows using MinGW runtime
string(APPEND TC_COMMON_FLAGS "--sysroot /usr/i686-w64-mingw32 -target i686-pc-windows-gnu")


# Common flags
string(APPEND TC_COMPILE_FLAGS "${TC_COMMON_FLAGS}")
# Use static linking so the DLL's are self-contained
string(APPEND TC_COMPILE_FLAGS " -static")
# Need __decltype(dllexport) and probably some other stuff
string(APPEND TC_COMPILE_FLAGS " -fms-extensions")
# sol2's autodetection of strerror_r existence is wrong
string(APPEND TC_COMPILE_FLAGS " -DCOMPAT53_HAVE_STRERROR_R=0")
# The runtime library already contains the typeinfo== operator, we can't have a
# duplicate symbol by defining it again.
string(APPEND TC_COMPILE_FLAGS " -D__GXX_TYPEINFO_EQUALITY_INLINE=0")
# MinGW include paths
string(APPEND TC_COMPILE_FLAGS " -I /usr/i686-w64-mingw32/include/c++/13.1.0/ -I /usr/i686-w64-mingw32/include/c++/13.1.0/i686-w64-mingw32")

set(CMAKE_C_FLAGS_INIT "${TC_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${TC_COMPILE_FLAGS}")

# Common flags
string(APPEND TC_LINK_FLAGS "${TC_COMMON_FLAGS}")
# Use ldd linker
string(APPEND TC_LINK_FLAGS " -fuse-ld=lld")
# MinGW library path
string(APPEND TC_LINK_FLAGS " -L /usr/lib/gcc/i686-w64-mingw32/13.1.0")

set(CMAKE_EXE_LINKER_FLAGS_INIT "${TC_LINK_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${TC_LINK_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${TC_LINK_FLAGS}")
