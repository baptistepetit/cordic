cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(fixed-point-cordic)

find_package(GTest REQUIRED)

add_compile_options(-std=c++14)

include_directories(
   "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

enable_testing()
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.test.cpp")
list(APPEND TEST_SOURCES ${SOURCES})
list(REMOVE_ITEM TEST_SOURCES EXCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_executable(
    ${PROJECT_NAME}-test
    ${TEST_SOURCES}
)
target_link_libraries(${PROJECT_NAME}-test gtest pthread)
gtest_add_tests(TARGET ${PROJECT_NAME}-test)
