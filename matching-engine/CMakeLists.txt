
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
    src/event.cpp
)
set_target_properties(matching-engine PROPERTIES POSITION_INDEPENDENT_CODE ON)

######## Simple Binary Encoding (SBE) ###########
set(schema "engine_schemas")
set(schema_path "${CMAKE_CURRENT_SOURCE_DIR}/sbe/${schema}.xml")
# mention one of the output files
set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}/external_include/sbepp-gen")
set(output_file "${output_dir}/${schema}.hpp")

# Generate sbe schema logic if sbepp is installed
# Otherwise use pre-generated code in repo
find_package(sbepp QUIET)
message(sbepp_FOUND="${sbepp_FOUND}")

if(sbepp_FOUND)
    # add a command which compiles the schema
    add_custom_command(
        OUTPUT ${output_file}
        COMMAND $<TARGET_FILE:sbepp::sbeppc> --output-dir ${output_dir} ${schema_path}
        DEPENDS "${schema_path}"
    )  

    # add a custom target which depends on the above
    add_custom_target(compile_schema
        DEPENDS ${output_file}
    )    

    add_dependencies(matching-engine compile_schema)
endif()
#################################################

# set the include directories
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external_include")
target_include_directories(matching-engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# python version of the lib
pybind11_add_module(matching_engine src/PyBinder.cpp)
target_link_libraries(matching_engine PRIVATE matching-engine)