cmake_minimum_required(VERSION 3.24)
project(SLAE)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(src/Matrix)
add_subdirectory(src/Solvers)
add_subdirectory(src/Decompositions)
add_subdirectory(tests)
add_subdirectory(KR1/4)



