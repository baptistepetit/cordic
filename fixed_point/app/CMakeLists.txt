########## Application Configuration

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} cordic-lib)
