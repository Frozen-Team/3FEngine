cmake_minimum_required(VERSION 3.3)

project(3dparty)

# TODO: We should (should we?) set suffixes for different architectures
# if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#   set(LIB_SUFFIX /x64)
# else()
#   set(LIB_SUFFIX /x86)
# endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/ CACHE PATH "Set install prefix" FORCE)
message(${CMAKE_INSTALL_PREFIX})

# Add SDL2
set(SDL_DIRECTX OFF CACHE BOOL "Don't use DirectX")
set(SDL_RENDER_D3D OFF CACHE BOOL "Don't use DirectX render")
set(SDL_SHARED OFF CACHE BOOL "Don't build shared library")
add_subdirectory(sdl)

# Add RapidJson
set(RAPIDJSON_HAS_STDSTRING ON CACHE BOOL "Enable sdt::string in RapidJson")
add_subdirectory(rapidjson)

# Add EntityX
add_subdirectory(entityx)

# Add Easyloggingpp
add_subdirectory(easyloggingpp)

# Add cppformat
set(FMT_DOC OFF CACHE BOOL "Don't generate doc")
add_subdirectory(cppformat)

# Add Eigen
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/eigen/cmake")
add_subdirectory(eigen/Eigen)