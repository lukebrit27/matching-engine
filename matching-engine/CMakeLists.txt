
# external projects
add_subdirectory(external_projects/pybind11)

# create python module with pybind
# this additionally creates a C++ library (since its a wrapper for add_library)
# regular cmake commands such target_include can be used on the produced target
add_library(matching-engine STATIC
    src/Book.cpp
    src/Engine.cpp
    src/Logger.cpp
    src/Order.cpp
    src/utils.cpp
)
set_target_properties(matching-engine PROPERTIES POSITION_INDEPENDENT_CODE ON)

# set the include directories
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external_include")
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

pybind11_add_module(matching_engine src/PyBinder.cpp)
target_link_libraries(matching_engine PRIVATE matching-engine)