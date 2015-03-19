
set(target smartio)
message("Lib ${target}")

# Collect all sources
file(GLOB SRC_INCLUDES "include/*.h" "include/*.hpp" "include/*.tpp")
file(GLOB SRC_CPP_FILES "cpp/*.cpp" "cpp/*.cxx")

# Binary files, those get added as blobs into the executable
file(GLOB SRC_BINARY RELATIVE res "res/*")

set(SRC_ALL_FILES ${SRC_CPP_FILES})


# Add the includes
include_directories(BEFORE "include")

set(ADDITIONAL_FLAGS "-fexceptions -std=c++11")

# Add the library as build
if(OPTION_BUILD_STATIC)
    set(BUILD_TYPE STATIC)
else()
    set(BUILD_TYPE SHARED)
endif()

add_library(${target} ${BUILD_TYPE} "${SRC_ALL_FILES}")

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


