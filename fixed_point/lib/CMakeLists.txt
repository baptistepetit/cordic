########## Library Configuration

add_library(
    cordic-lib
    INTERFACE
)

target_sources(
    cordic-lib
    INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

target_include_directories(
    cordic-lib
    INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)


########## Library test Configuration

enable_testing()
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.test.cpp")

add_executable(
    cordic-lib-test
    ${TEST_SOURCES}
)

target_link_libraries(cordic-lib-test gtest gmock pthread cordic-lib)
gtest_add_tests(TARGET cordic-lib-test)
