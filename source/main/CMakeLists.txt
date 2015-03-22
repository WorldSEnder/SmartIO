
set(target smartio)
message("Lib ${target}")

# Collect all sources
file(GLOB_RECURSE SRC_INCLUDES
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.tpp")
file(GLOB_RECURSE SRC_CPP_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cxx")

# Binary files, those get added as blobs into the executable
file(GLOB_RECURSE SRC_BINARY
     RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/res/"
     "${CMAKE_CURRENT_SOURCE_DIR}/res/*")

set(SRC_ALL_FILES ${SRC_CPP_FILES})


# Add the includes
include_directories(BEFORE "include")

set(ADDITIONAL_FLAGS "-fexceptions -std=c++11")

# Add the library as build

message("Found sources: ${SRC_ALL_FILES}")
add_library(${target} "${SRC_ALL_FILES}")

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    VERSION                     "${META_VERSION}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS} ${ADDITIONAL_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")


