cmake_minimum_required(VERSION 3.0)

project(3DEngine)

include(ExternalProject)
include(CMakeDependentOption)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# set(SDL_SOURCES_E "${CMAKE_SOURCE_DIR}/3dparty/sdl")
# set(SDL_PREFIX_E "${CMAKE_SOURCE_DIR}/3dparty/sdl/build")
# set(SDL_INSTALL_DIR_E "${CMAKE_SOURCE_DIR}/3dparty/builds/SDL/")
# set(SDL_CMAKE_ARGS_E "-DCMAKE_INSTALL_PREFIX=${SDL_INSTALL_DIR_E}")

# list(APPEND SDL_CMAKE_ARGS_E "-DDIRECTX=OFF")
# list(APPEND SDL_CMAKE_ARGS_E "-DSDL_BUILDING_LIBRARY=ON")
# list(APPEND SDL_CMAKE_ARGS_E "-DSDL_SHARED=OFF")

# ExternalProject_Add(SDL_LIB 
# 	SOURCE_DIR ${SDL_SOURCES_E} 
# 	PREFIX ${SDL_PREFIX_E} 
# 	INSTALL_DIR ${SDL_INSTALL_DIR_E}
# 	CMAKE_ARGS ${SDL_CMAKE_ARGS_E}
# 	) 

# Set path to Engine's third party installation directory.
set(ENGINE_3DPARTY_DIR "${CMAKE_SOURCE_DIR}/3dparty/builds/")

# Find RapidJSON
set(ENV{RAPIDJSONDIR} ${ENGINE_3DPARTY_DIR})
find_package(RAPIDJSON REQUIRED)
if(RAPIDJSON_FOUND)
	message("RapidJSON is found.")
else(RAPIDJSON_FOUND)
	message("Cannot locate RapidJSON.")
endif(RAPIDJSON_FOUND)

# Find SDL2
set(ENV{SDL2DIR} ${ENGINE_3DPARTY_DIR})
# set(SDL2_BUILDING_LIBRARY "True")
find_package(SDL2 REQUIRED)

if(SDL2_FOUND)
	message("SDL version: ${SDL2_VE}")
else(SDL2_FOUND)
	message("Cannot locate SDL.")
endif(SDL2_FOUND)

#Find EntityX
set(ENV{ENTITYX_ROOT} ${ENGINE_3DPARTY_DIR})

find_package(ENTITYX REQUIRED)

if(ENTITYX_FOUND)
	message("EntityX is found.")
else(ENTITYX_FOUND)
	message("Cannot locate EntityX.")
endif(ENTITYX_FOUND)


message("Include dir:")
message(STATUS ${SDL2_INCLUDE_DIR})
message(STATUS ${SDL2MAIN_LIBRARY})
message(STATUS ${RAPIDJSON_INCLUDE_DIR})
message(STATUS ${ENTITYX_INCLUDE_DIR})




# TODO: Add filters for game src
file(GLOB GAME_SOURCES  game-src/*.cpp game-src/*.h)

add_executable(game ${GAME_SOURCES})
target_link_libraries(game ${SDL2_LIBRARY}) 
target_link_libraries(game ${SDL2MAIN_LIBRARY})

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(game PUBLIC ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(game PUBLIC ${ENTITYX_INCLUDE_DIR})
