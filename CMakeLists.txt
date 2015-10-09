cmake_minimum_required(VERSION 3.0)

include(ExternalProject)
include(CMakeDependentOption)

project(FEngine)

set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"LIBCMT\")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MDd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIBS_INSTALL_SUFFIX /x64)
else()
  set(LIBS_INSTALL_SUFFIX /x86)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# Set path to Engine's third party installation directory.
set(ENGINE_3DPARTY_DIR "${CMAKE_SOURCE_DIR}/3dparty/install/${LIBS_INSTALL_SUFFIX}")

# Make a list of extra runtime libraries.
list(APPEND ENGINE_EXTRA_LIBS user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)

set(ENGINE_DEFAULT_FBX_VERSION "2016.1.2")

# Make the options to define custom library path.
option(ENGINE_RAPIDJSONDIR "RapidJSON root path." ${ENGINE_3DPARTY_DIR})
option(ENGINE_SDL2DIR "SDL2 root path." ${ENGINE_3DPARTY_DIR})
option(ENGINE_ENTITYX_ROOT "EntityX root path." ${ENGINE_3DPARTY_DIR})
option(ENGINE_EASYLOGGINGPP_ROOT "easyloggingpp root path." ${ENGINE_3DPARTY_DIR})
option(ENGINE_CPPFORMAT_ROOT "cppformat root path." ${ENGINE_3DPARTY_DIR})
option(ENGINE_EIGEN_ROOT "Eigen root path." ${ENGINE_3DPARTY_DIR})
option(ENGINE_FBXSDK_VESION "The FBX SDK version to find." ${ENGINE_DEFAULT_FBX_VERSION})
option(ENGINE_FBXSDK_ROOT "FBX SDK root path." ${ENGINE_3DPARTY_DIR})

# Find RapidJSON, SDL2, EntityX, Easyloggingpp, Cppformat, OpenGL, FBX SDK
set(ENV{RAPIDJSONDIR} ${ENGINE_RAPIDJSONDIR})
set(ENV{SDL2DIR} ${ENGINE_SDL2DIR})
# set(SDL2_BUILDING_LIBRARY "True")
set(ENV{ENTITYX_ROOT} ${ENGINE_ENTITYX_ROOT})
set(ENV{EASYLOGGINGPP_ROOT} ${ENGINE_EASYLOGGINGPP_ROOT})
set(ENV{CPPFORMAT_ROOT} ${ENGINE_CPPFORMAT_ROOT})
set(ENV{EIGEN_ROOT} ${ENGINE_EIGEN_ROOT})
set(ENV{FBXSDK_ROOT} ${ENGINE_EIGEN_ROOT})

find_package(RapidJSON REQUIRED)
find_package(SDL2 REQUIRED)
find_package(EntityX REQUIRED)
find_package(easyloggingpp REQUIRED)
find_package(cppformat REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen REQUIRED)
find_package(FBXSDK REQUIRED)

file(GLOB GAME_SOURCES  game-src/*.cpp game-src/*.h)

add_executable(game ${GAME_SOURCES})

target_link_libraries(game ${SDL2_LIBRARY}) 
target_link_libraries(game ${SDL2MAIN_LIBRARY})
target_link_libraries(game ${CPPFORMAT_LIBRARY})
target_link_libraries(game ${OPENGL_LIBRARIES})
target_link_libraries(game ${ENGINE_EXTRA_LIBS})

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(game PUBLIC ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(game PUBLIC ${ENTITYX_INCLUDE_DIR})
target_include_directories(game PUBLIC ${EASYLOGGINGPP_INCLUDE_DIR})
target_include_directories(game PUBLIC ${CPPFORMAT_INCLUDE_DIR})
target_include_directories(game PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(game PUBLIC ${EIGEN3_INCLUDE_DIR})

