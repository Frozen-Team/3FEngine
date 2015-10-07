# TODO: compiler flags
cmake_minimum_required(VERSION 3.0)

project(3DEngine)

include(ExternalProject)
include(CMakeDependentOption)

# TODO: Use modules from corresponding library directories
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3dparty/eigen/cmake")



# Set path to Engine's third party installation directory.
set(ENGINE_3DPARTY_DIR "${CMAKE_SOURCE_DIR}/3dparty/install/")

# Find RapidJSON, SDL2, EntityX, Easyloggingpp, Cppformat, OpenGL
set(ENV{RAPIDJSONDIR} ${ENGINE_3DPARTY_DIR})
set(ENV{SDL2DIR} ${ENGINE_3DPARTY_DIR})
# set(SDL2_BUILDING_LIBRARY "True")
set(ENV{ENTITYX_ROOT} ${ENGINE_3DPARTY_DIR})
set(ENV{EASYLOGGINGPP_ROOT} ${ENGINE_3DPARTY_DIR})
set(ENV{CPPFORMAT_ROOT} ${ENGINE_3DPARTY_DIR})
set(ENV{EIGEN3_ROOT} ${ENGINE_3DPARTY_DIR})

find_package(RapidJSON REQUIRED)
find_package(SDL2 REQUIRED)
find_package(EntityX REQUIRED)
find_package(easyloggingpp REQUIRED)
find_package(cppformat REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3)

message(${EIGEN3_VERSION})

# TODO: Add filters for game src
file(GLOB GAME_SOURCES  game-src/*.cpp game-src/*.h)

add_executable(game ${GAME_SOURCES})
target_link_libraries(game ${SDL2_LIBRARY}) 
target_link_libraries(game ${SDL2MAIN_LIBRARY})
target_link_libraries(game ${CPPFORMAT_LIBRARY})
target_link_libraries(game ${OPENGL_LIBRARIES})

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(game PUBLIC ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(game PUBLIC ${ENTITYX_INCLUDE_DIR})
target_include_directories(game PUBLIC ${EASYLOGGINGPP_INCLUDE_DIR})
target_include_directories(game PUBLIC ${CPPFORMAT_INCLUDE_DIR})
target_include_directories(game PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(game PUBLIC ${EIGEN3_INCLUDE_DIR})