cmake_minimum_required(VERSION 3.0)

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
set(ENGINE_FBXSDK_ROOT ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "FBX SDK root path.")
set(ENGINE_GLI_ROOT ${ENGINE_3DPARTY_DIR_ARCH} CACHE STRING "GLI root path.")

function(SET_LIB_ROOT_PATH VAR VALUE)
	if(NOT DEFINED ${VAR} AND NOT DEFINED ENV{${VAR}})
		set(ENV{${VAR}} ${VALUE})
	endif()
endfunction(SET_LIB_ROOT_PATH)

SET_LIB_ROOT_PATH(RAPIDJSONDIR ${ENGINE_RAPIDJSONDIR})
SET_LIB_ROOT_PATH(SDL2DIR ${ENGINE_SDL2DIR})
SET_LIB_ROOT_PATH(ENTITYX_ROOT ${ENGINE_ENTITYX_ROOT})
SET_LIB_ROOT_PATH(EASYLOGGINGPP_ROOT ${ENGINE_EASYLOGGINGPP_ROOT})
SET_LIB_ROOT_PATH(CPPFORMAT_ROOT ${ENGINE_CPPFORMAT_ROOT})
SET_LIB_ROOT_PATH(EIGEN_ROOT ${ENGINE_EIGEN_ROOT})
SET_LIB_ROOT_PATH(FBXSDK_ROOT ${ENGINE_3DPARTY_INSTALL})
SET_LIB_ROOT_PATH(GLI_ROOT ${ENGINE_GLI_ROOT})

# Find RapidJSON, SDL2, EntityX, Easyloggingpp, Cppformat, OpenGL, FBX SDK
find_package(RapidJSON REQUIRED)
find_package(SDL2 REQUIRED)
find_package(EntityX REQUIRED)
find_package(easyloggingpp REQUIRED)
find_package(cppformat REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen REQUIRED)
find_package(FBXSDK REQUIRED)
find_package(GLI REQUIRED)

set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Set engine include directory")


file(GLOB_RECURSE ENGINE_SOURCES  
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}/*.h 
		${CMAKE_CURRENT_SOURCE_DIR}/*.hpp 
		${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
)

# workaroung to remove fbx2fseq out of 3FEngine src
set (ENGINE_EXCLUDE_DIR "/fbx2fseq/")
foreach (TMP_PATH ${ENGINE_SOURCES})
    string (FIND ${TMP_PATH} ${ENGINE_EXCLUDE_DIR} ENGINE_EXCLUDE_DIR_FOUND)
    if (NOT ${ENGINE_EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM ENGINE_SOURCES ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

foreach(f ${ENGINE_SOURCES})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)
    file(RELATIVE_PATH SRCGR ${CMAKE_CURRENT_SOURCE_DIR} ${f})
    set(SRCGR "src/${SRCGR}")

    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

add_library(3FEngine ${ENGINE_SOURCES})

target_include_directories(3FEngine PUBLIC ${ENGINE_INCLUDE_DIR})

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

target_link_libraries(3FEngine ${SDL_LINK_LIST} ${SDL_LINK_LIST_DEBUG})
# target_link_libraries(game optimized ${SDL2MAIN_LIBRARY} DEBUG ${SDL2MAIN_LIBRARY_DEBUG})
target_link_libraries(3FEngine optimized ${CPPFORMAT_LIBRARY} debug ${CPPFORMAT_LIBRARY_DEBUG})
target_link_libraries(3FEngine optimized ${FBXSDK_LIBRARY} debug ${FBXSDK_LIBRARY_DEBUG})
target_link_libraries(3FEngine ${OPENGL_LIBRARIES})
target_link_libraries(3FEngine ${ENGINE_EXTRA_LIBS})

target_include_directories(3FEngine PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${ENTITYX_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${EASYLOGGINGPP_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${CPPFORMAT_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${EIGEN3_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${FBXSDK_INCLUDE_DIR})
target_include_directories(3FEngine PUBLIC ${GLI_INCLUDE_DIR})

#
# fbx2fseq project
#
file(GLOB_RECURSE FBX2FSEQ_SOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/fbx2fseq/*.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/fbx2fseq/*.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/fbx2fseq/*.hpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/fbx2fseq/*.cxx
)

add_executable(fbx2fseq ${FBX2FSEQ_SOURCES}) 
set_target_properties(fbx2fseq PROPERTIES DEBUG_POSTFIX -d)
if(MSVC)
    set_target_properties(fbx2fseq PROPERTIES LINK_FLAGS_RELEASE ${ENGINE_WIN_SUBSYSTEM})
    message(${ENGINE_WIN_SUBSYSTEM})
    set_target_properties(fbx2fseq PROPERTIES LINK_FLAGS_DEBUG ${ENGINE_WIN_SUBSYSTEM})
    set_target_properties(fbx2fseq PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_DEPLOY_DIR} )
    message(${ENGINE_DEPLOY_DIR})
    set_target_properties(fbx2fseq PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ENGINE_DEPLOY_DIR} )
    set_target_properties(fbx2fseq PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ENGINE_DEPLOY_DIR} )
endif()

target_link_libraries(fbx2fseq optimized ${FBXSDK_LIBRARY} debug ${FBXSDK_LIBRARY_DEBUG})
target_link_libraries(fbx2fseq ${ENGINE_EXTRA_LIBS})

target_include_directories(fbx2fseq PUBLIC ${FBXSDK_INCLUDE_DIR})