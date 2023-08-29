cmake_minimum_required(VERSION 3.0.0)
project(matching-engine VERSION 0.1.0 LANGUAGES C CXX)
include(ExternalProject)

# Set the path to the source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Set paths to the include directories
# set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# set(EXTERNAL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external_include")

# Collect all the .cpp files from the source directory
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cpp")


# add library
add_library(matching-engine SHARED 
    src/Book.cpp
    src/Logger.cpp
    src/Order.cpp
    src/utils.cpp
)

# set the include directories
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external_include")
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
