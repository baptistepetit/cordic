cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(fixed-point-cordic)

find_package(GTest REQUIRED)

include(_cmake/gcc_flags.cmake)

add_compile_options(-std=c++14 ${GCC_WARNING_FLAGS})

add_subdirectory(lib)
add_subdirectory(app)
