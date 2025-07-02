cmake_minimum_required(VERSION 4.0)
project(sum C)

set(CMAKE_C_STANDARD 11)

# Create static library for sum
add_library(sum STATIC sum.c)

# Build test executable
add_executable(test_sum test_sum.c)

# Link test executable with sum library and pthread for threading
target_link_libraries(test_sum PRIVATE sum pthread)
