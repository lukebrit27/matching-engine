cmake_minimum_required(VERSION 3.0.0)
project(matching-engine VERSION 0.1.0 LANGUAGES C CXX)

# Set the path to the source directory
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Collect all the .cpp files from the source directory
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# add executable
add_executable(matching-engine ${SOURCES})

# set the include directories
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external_include")
target_include_directories(matching-engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# add dependencies
# include(ExternalProject)
# include(CPack)
