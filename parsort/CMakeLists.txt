cmake_minimum_required(VERSION 4.0)
project(parsort C)

set(CMAKE_C_STANDARD 11)

# Create static library for parsort
add_library(parsort STATIC parsort.c)

# Build test executable
add_executable(test_parsort test_parsort.c)

# Link test executable with parsort library and pthread for threading
target_link_libraries(test_parsort PRIVATE parsort pthread)
