########## Measure Error Configuration

add_executable(
    measure-error-app
    "${CMAKE_CURRENT_SOURCE_DIR}/src/measure_error.cpp"
)

target_include_directories(
    measure-error-app
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(measure-error-app cordic-lib)


########## Print Fixed Point Configuration

add_executable(
    print-fixed-point-app
    "${CMAKE_CURRENT_SOURCE_DIR}/src/print_fixed_point.cpp"
)

target_link_libraries(print-fixed-point-app cordic-lib)


########## Generate Cordic Pipeline Configuration

add_executable(
    generate-cordic-pipeline-app
    "${CMAKE_CURRENT_SOURCE_DIR}/src/generate_cordic_pipeline.cpp"
)

target_include_directories(
    generate-cordic-pipeline-app
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(generate-cordic-pipeline-app cordic-lib)
