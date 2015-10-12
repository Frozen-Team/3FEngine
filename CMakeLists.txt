cmake_minimum_required(VERSION 3.0)

include(ExternalProject)
include(CMakeDependentOption)

project(Game)

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

add_subdirectory(src)

file(GLOB_RECURSE GAME_SOURCES 	${CMAKE_CURRENT_SOURCE_DIR}/game-src/*.cpp
								${CMAKE_CURRENT_SOURCE_DIR}/game-src/*.h 
								${CMAKE_CURRENT_SOURCE_DIR}/game-src/*.cxx 
								${CMAKE_CURRENT_SOURCE_DIR}/game-src/*.hpp 
)

foreach(f ${GAME_SOURCES})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)
    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_SOURCE_DIR}/game-src ${f})
    set(SRCGR "src/${SRCGR}")

    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()


add_executable(game ${GAME_SOURCES})
set_target_properties(game PROPERTIES DEBUG_POSTFIX -d)
if(MSVC)
	set_target_properties(game PROPERTIES LINK_FLAGS_RELEASE ${ENGINE_WIN_SUBSYSTEM})
	set_target_properties(game PROPERTIES LINK_FLAGS_DEBUG ${ENGINE_WIN_SUBSYSTEM})
	set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_DEPLOY_DIR} )
    set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ENGINE_DEPLOY_DIR} )
    set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ENGINE_DEPLOY_DIR} )
endif()
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/deploy")

target_link_libraries(game 3FEngine)
target_include_directories(game PUBLIC ${ENGINE_INCLUDE_DIR})