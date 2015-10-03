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


#set(ENV{SDL2DIR} "${CMAKE_SOURCE_DIR}/3dparty/builds/sdl")
#message("hello")
#message($ENV{SDL2DIR})



# set(SDL2_BUILDING_LIBRARY "True")

find_package(SDL2 REQUIRED)

if(SDL2_FOUND)
	message("SDL version: ${SDL2_VE}")
endif(SDL2_FOUND)

message("Include dir:")
message(STATUS ${SDL2_INCLUDE_DIR})
message(STATUS ${SDL2MAIN_LIBRARY})




# TODO: Add filters for game src
file(GLOB GAME_SOURCES  game-src/*.cpp game-src/*.h)

add_executable(game ${GAME_SOURCES})
target_link_libraries(game ${SDL2_LIBRARY}) 
target_link_libraries(game ${SDL2MAIN_LIBRARY})
target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIR})
