
# add library
add_library(matching-engine SHARED 
    src/Book.cpp
    src/Engine.cpp
    src/Logger.cpp
    src/Order.cpp
    src/utils.cpp
)

# set the include directories
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external_include")
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
