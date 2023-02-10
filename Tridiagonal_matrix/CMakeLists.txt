cmake_minimum_required(VERSION 3.16)
project(Tridiagonal_matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tridiagonal_matrix TridiagonalMatrix.h tests_tridiagonal.cpp TridiagonalMatrix_solver.h)
target_link_libraries(Tridiagonal_matrix gtest pthread)

