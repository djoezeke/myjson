cmake_minimum_required(VERSION 3.12)
project(Jsonfy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library target
add_library(jsonfy STATIC
    myjson.cpp
    myjson.hpp
)

target_include_directories(jsonfy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Example executable (optional)
add_executable(jsonfy_example examples/basic.cpp)
target_link_libraries(jsonfy_example PRIVATE jsonfy)

# Test executable (optional)
enable_testing()
add_executable(jsonfy_test tests/test.cpp)
target_link_libraries(jsonfy_test