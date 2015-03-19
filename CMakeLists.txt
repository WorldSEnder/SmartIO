
cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

# Project description and (meta) information

set(META_PROJECT_NAME        "smartio")
set(META_PROJECT_DESCRIPTION "A fast-to-use library to import binary files into C++-classes")
set(META_VERSION_MAJOR       "0")
set(META_VERSION_MINOR       "1")
set(META_VERSION_PATCH       "1")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_AUTHOR_DOMAIN       "https://github.com/WorldSEnder/SmartIO")
set(META_AUTHOR_MAINTAINER   "martin.molzer@gmx.de")

project ("SmartIO" CXX)

# Options

option(OPTION_BUILD_STATIC "Build static libraries" OFF)
option(OPTION_BUILD_TESTS "Build tests" ON)

if(OPTION_BUILD_STATIC)
    set(BUILD_SHARED_LIBS OFF)
else()
    set(BUILD_SHARED_LIBS ON)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(source)

