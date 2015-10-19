cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE FBX2FSEQ_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
)

message("FBX2FSEQ_BEG")
message(${FBX2FSEQ_SOURCES})
message(${CMAKE_CURRENT_SOURCE_DIR})
message("FBX2FSEQ_END")
ADD_FILTERS("${FBX2FSEQ_SOURCES}" ${CMAKE_CURRENT_SOURCE_DIR})

find_package(FBXSDK REQUIRED)

add_executable(fbx2fseq ${FBX2FSEQ_SOURCES}) 
set_target_properties(fbx2fseq PROPERTIES DEBUG_POSTFIX -d)
if(MSVC)
    set_target_properties(fbx2fseq PROPERTIES LINK_FLAGS_RELEASE ${ENGINE_WIN_SUBSYSTEM})
    set_target_properties(fbx2fseq PROPERTIES LINK_FLAGS_DEBUG ${ENGINE_WIN_SUBSYSTEM})
    set_target_properties(fbx2fseq PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${ENGINE_DEPLOY_DIR})
    set_target_properties(fbx2fseq PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ENGINE_DEPLOY_DIR})
    set_target_properties(fbx2fseq PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ENGINE_DEPLOY_DIR})
endif()

target_link_libraries(fbx2fseq optimized ${FBXSDK_LIBRARY} debug ${FBXSDK_LIBRARY_DEBUG})
target_link_libraries(fbx2fseq ${ENGINE_EXTRA_LIBS})
target_link_libraries(fbx2fseq 3FEngine)

target_include_directories(fbx2fseq PUBLIC ${FBXSDK_INCLUDE_DIR})
target_include_directories(fbx2fseq PUBLIC ${ENGINE_INCLUDE_DIR})