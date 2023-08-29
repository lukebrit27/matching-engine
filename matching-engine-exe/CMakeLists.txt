# add executable
add_executable(matching-engine-exe src/main.cpp)

target_link_libraries(matching-engine-exe PRIVATE matching-engine)