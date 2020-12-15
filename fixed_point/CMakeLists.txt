cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(fixed-point-cordic)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
