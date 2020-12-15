cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(fixed-point-cordic)

find_package(GTest REQUIRED)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

enable_testing()
add_executable(
    ${PROJECT_NAME}-test
    ${CMAKE_CURRENT_SOURCE_DIR}/test/main.test.cpp
)
target_link_libraries(${PROJECT_NAME}-test gtest pthread)
gtest_add_tests(TARGET ${PROJECT_NAME}-test)
