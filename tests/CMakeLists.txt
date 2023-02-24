cmake_minimum_required(VERSION 3.24)
project(SLAE)
# GTest include code would
# go somewhere in here

add_executable(test_trid tests_tridiagonal.cpp)
add_executable(test_csr tests_CSR.cpp)
add_executable(test_dense tests_dense.cpp)

find_package(GTest REQUIRED)

target_link_libraries(test_trid
        PRIVATE
        GTest::GTest)

target_link_libraries(test_csr
        PRIVATE
        GTest::GTest)

target_link_libraries(test_dense
        PRIVATE
        GTest::GTest)


add_test(gtests test_trid test_csr tests_dense.cpp)
