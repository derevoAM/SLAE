cmake_minimum_required(VERSION 3.24)
project(SLAE CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE files *.h)

add_library(Solvers INTERFACE ${files})