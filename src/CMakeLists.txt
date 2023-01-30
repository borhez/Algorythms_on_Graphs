cmake_minimum_required(VERSION 3.22)
project(Navigator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test/googletest-main) # почему именно subdirectory
include_directories(test/googletest-main/googletest/include)

add_executable(Navigator
#        navigator/test.cpp
        navigator/s21_graph/s21_graph.cpp navigator/s21_graph/s21_graph.h
        navigator/matrix/Matrix.cpp navigator/matrix/Matrix.hpp
        navigator/s21_graph/s21_graph_algorithms.h navigator/s21_graph/s21_graph_algorithms.cpp
        navigator/stack/Stack.hpp
        test/graphTest.cpp
        )
target_link_libraries(Navigator gtest gtest_main)
