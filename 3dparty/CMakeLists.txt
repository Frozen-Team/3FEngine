cmake_minimum_required(VERSION 3.3)

project(3dparty)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIBS_INSTALL_SUFFIX /x64)
else()
  set(LIBS_INSTALL_SUFFIX /x86)
endif()

if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"LIBCMT\")
endif()

# TODO: Add check if solution generates for Visual Studio
#set(PDB_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/install/${LIBS_INSTALL_SUFFIX}/lib CACHE PATH "Set path to store PDB files")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/${LIBS_INSTALL_SUFFIX}/ CACHE PATH "Set install prefix" FORCE)


set(gtest_force_shared_crt ON CACHE BOOL "Force shared crt")
set(BUILD_TESTING OFF CACHE BOOL "Don't build tests")

# Add SDL2
set(SDL_DIRECTX OFF CACHE BOOL "Don't use DirectX")
set(SDL_RENDER_D3D OFF CACHE BOOL "Don't use DirectX render")
set(SDL_SHARED OFF CACHE BOOL "Don't build shared library")
add_subdirectory(sdl)

# Add RapidJson
set(RAPIDJSON_HAS_STDSTRING ON CACHE BOOL "Enable sdt::string in RapidJson")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "Disable building examples for RapidJSON")
set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "Disable building RapidJson documentation")
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Disable building RapidJson tests")
add_subdirectory(rapidjson)

# Add EntityX
set(ENTITYX_BUILD_TESTING OFF CACHE BOOL "Disable test building for EntityX")
set(ENTITYX_BUILD_SHARED OFF CACHE BOOL "Disable building shared version of EntityX")
add_subdirectory(entityx)

# Add Easyloggingpp
add_subdirectory(easyloggingpp)

# Add cppformat
set(FMT_DOC OFF CACHE BOOL "Don't generate cppformat documentation for cppformat")
set(FMT_TEST OFF CACHE BOOL "Disable test building for cppformat")
add_subdirectory(cppformat)

# Add Eigen
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/eigen/cmake")
# Workaround for Eigen
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include CACHE PATH "Set install prefix for includes" FORCE)
add_subdirectory(eigen/Eigen)