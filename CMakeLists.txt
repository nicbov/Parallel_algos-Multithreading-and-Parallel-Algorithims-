cmake_minimum_required(VERSION 3.10)
project(parallel_algos C)

set(CMAKE_C_STANDARD 11)

add_executable(test_sum sum/test_sum.c sum/sum.c)
