cmake_minimum_required(VERSION 3.24)
project(SLAE)

file(GLOB files "*.cpp")

foreach (file ${files})
    get_filename_component(TName ${file} NAME)
    add_executable("${TName}" ${file})
endforeach ()