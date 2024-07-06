cmake_minimum_required(VERSION 3.5)
project(tetris++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE game_headers structs/game/*.hpp)
file(GLOB_RECURSE game_sources structs/game/*.cpp)

file(GLOB_RECURSE piece_headers structs/piece/*.hpp)
file(GLOB_RECURSE piece_sources structs/piece/*.cpp)

file(GLOB_RECURSE piece_grid_headers structs/piece_grid/*.hpp)
file(GLOB_RECURSE piece_grid_sources structs/piece_grid/*.cpp)

# Build the project and the library
add_library(${PROJECT_NAME} ${game_headers} ${game_sources} ${piece_headers} ${piece_sources} ${piece_grid_headers} ${piece_grid_sources})

# gtest

add_subdirectory(external/googletest)
include_directories(external/googletest/googletest/include)


# Testing
enable_testing()

# Build the test executable and link against the main library and gtest
file(GLOB_RECURSE TESTS tests/*.cpp)
add_executable(tetris_test ${TESTS})
include_directories(structs/piece structs/piece_grid)
target_link_libraries(tetris_test gtest_main ${PROJECT_NAME})


# Register the test executable with CTest
add_test(NAME tetris_test COMMAND tetris_test)