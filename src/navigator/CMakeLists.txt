cmake_minimum_required(VERSION 3.22)
project(Navi)

set(CMAKE_CXX_STANDARD 17)

add_executable(Navigator test.cpp s21_graph/s21_graph.cpp s21_graph/s21_graph.h matrix/Matrix.cpp matrix/Matrix.hpp s21_graph/s21_graph_algorithms.h s21_graph/s21_graph_algorithms.cpp stack/Stack.hpp)
