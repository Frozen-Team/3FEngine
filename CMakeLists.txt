cmake_minimum_required(VERSION 3.0)

include(ExternalProject)
include(CMakeDependentOption)

project(3FEngine)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIBS_INSTALL_SUFFIX x64)
else()
  set(LIBS_INSTALL_SUFFIX x86)
endif()

# set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"LIBCMT\")
# set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"MSVCRT\")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Allow Debug and Release configurations only." FORCE)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/deploy")

if(MSVC)
	option(ENGINE_ENABLE_CONSOLE "Enable console window." ON)
	if(ENGINE_ENABLE_CONSOLE)
		set(ENGINE_WIN_SUBSYSTEM "/SUBSYSTEM:CONSOLE")
	else()
		set(ENGINE_WIN_SUBSYSTEM "/SUBSYSTEM:WINDOWS")
	endif()
endif()

set(ENGINE_DEPLOY_DIR "${CMAKE_SOURCE_DIR}/deploy")

# Set path to Engine's third party installation directory.
set(ENGINE_3DPARTY_INSTALL "${CMAKE_SOURCE_DIR}/3dparty/install")
set(ENGINE_3DPARTY_DIR_ARCH "${ENGINE_3DPARTY_INSTALL}/${LIBS_INSTALL_SUFFIX}")

# Make a list of extra runtime libraries.
list(APPEND ENGINE_EXTRA_LIBS user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)

set(ENGINE_DEFAULT_FBX_VERSION "2016.1.2")

# Make the options to define custom library path.
set(ENGINE_RAPIDJSONDIR ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "RapidJSON root path.")
set(ENGINE_SDL2DIR ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "SDL2 root path.")
set(ENGINE_ENTITYX_ROOT ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "EntityX root path.")
set(ENGINE_EASYLOGGINGPP_ROOT ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "easyloggingpp root path.")
set(ENGINE_CPPFORMAT_ROOT ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "cppformat root path." )
set(ENGINE_EIGEN_ROOT ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "Eigen root path.")
set(ENGINE_FBXSDK_VESION ${ENGINE_DEFAULT_FBX_VERSION} CACHE STRING "The FBX SDK version to find.")

# Find RapidJSON, SDL2, EntityX, Easyloggingpp, Cppformat, OpenGL, FBX SDK
set(ENV{RAPIDJSONDIR} ${ENGINE_RAPIDJSONDIR})
set(ENV{SDL2DIR} ${ENGINE_SDL2DIR})
# set(SDL2_BUILDING_LIBRARY "True")
set(ENV{ENTITYX_ROOT} ${ENGINE_ENTITYX_ROOT})
set(ENV{EASYLOGGINGPP_ROOT} ${ENGINE_EASYLOGGINGPP_ROOT})
set(ENV{CPPFORMAT_ROOT} ${ENGINE_CPPFORMAT_ROOT})
set(ENV{EIGEN_ROOT} ${ENGINE_EIGEN_ROOT})
if (NOT DEFINED ENV{FBXSDK_ROOT})
	set(ENV{FBXSDK_ROOT} ${ENGINE_3DPARTY_INSTALL})
endif()


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
set_target_properties(game PROPERTIES DEBUG_POSTFIX -d)
if(MSVC)
	message(${MSVC})
	set_target_properties(game PROPERTIES LINK_FLAGS_RELEASE ${ENGINE_WIN_SUBSYSTEM})
	set_target_properties(game PROPERTIES LINK_FLAGS_DEBUG ${ENGINE_WIN_SUBSYSTEM})
	set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_DEPLOY_DIR} )
    set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ENGINE_DEPLOY_DIR} )
    set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ENGINE_DEPLOY_DIR} )
endif()
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/deploy")

# Make a list of sdl debug libraries
set (SDL_LINK_LIST_DEBUG "")
foreach(l ${SDL2_LIBRARY_DEBUG})
    list (APPEND SDL_LINK_LIST_DEBUG debug ${l})
endforeach()
# Make a list of sdl release libraries
set (SDL_LINK_LIST "")
foreach(l ${SDL2_LIBRARY})
    list (APPEND SDL_LINK_LIST optimized ${l})
endforeach()

target_link_libraries(game ${SDL_LINK_LIST} ${SDL_LINK_LIST_DEBUG})
# target_link_libraries(game optimized ${SDL2MAIN_LIBRARY} DEBUG ${SDL2MAIN_LIBRARY_DEBUG})
target_link_libraries(game optimized ${CPPFORMAT_LIBRARY} debug ${CPPFORMAT_LIBRARY_DEBUG})
target_link_libraries(game optimized ${FBXSDK_LIBRARY} debug ${FBXSDK_LIBRARY_DEBUG})
target_link_libraries(game ${OPENGL_LIBRARIES})
target_link_libraries(game ${ENGINE_EXTRA_LIBS})

target_include_directories(game PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(game PUBLIC ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(game PUBLIC ${ENTITYX_INCLUDE_DIR})
target_include_directories(game PUBLIC ${EASYLOGGINGPP_INCLUDE_DIR})
target_include_directories(game PUBLIC ${CPPFORMAT_INCLUDE_DIR})
target_include_directories(game PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(game PUBLIC ${EIGEN3_INCLUDE_DIR})
target_include_directories(game PUBLIC ${FBXSDK_INCLUDE_DIR})

