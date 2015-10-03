cmake_minimum_required(VERSION 3.3)

project(3dparty)

# TODO: We should (should we?) set suffixes for different architectures
# if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#   set(LIB_SUFFIX /x64)
# else()
#   set(LIB_SUFFIX /x86)
# endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/builds/sdl/ CACHE PATH "Set install prefix for SDL" FORCE)
message(${CMAKE_INSTALL_PREFIX})
add_subdirectory(./sdl)