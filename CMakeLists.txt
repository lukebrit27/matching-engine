cmake_minimum_required(VERSION 3.0.0)
project(matching-engine VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

add_subdirectory(matching-engine)
add_subdirectory(matching-engine-exe)
