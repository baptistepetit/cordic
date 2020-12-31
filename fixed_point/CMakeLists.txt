cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(fixed-point-cordic)

find_package(GTest REQUIRED)

add_compile_options(-std=c++14)

add_subdirectory(lib)
add_subdirectory(app)
