cmake_minimum_required(VERSION 3.10)

project(hello VERSION 0.1)

add_library(hello_compiler_flags INTERFACE)
target_compile_features(hello_compiler_flags INTERFACE cxx_std_11)
target_compile_options(hello_compiler_flags INTERFACE 
    -Wall -Wextra -Wpedantic
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(hello_compiler_flags INTERFACE 
        -O0 -coverage
    )
    target_link_options(hello_compiler_flags INTERFACE 
        -coverage
    )
endif()

find_package(CLI11 CONFIG REQUIRED)

add_executable(hello src/main.cc src/func.cc)

target_link_libraries(hello PRIVATE hello_compiler_flags)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_program(lcov lcov)
    find_program(genhtml genhtml)

    if(lcov AND genhtml)
        message(STATUS "lcov found: ${lcov}")
        message(STATUS "genhtml found: ${genhtml}")

        add_custom_target(collect_coverage_init
            COMMAND ${lcov} -c -i -d . -o base.info --branch-coverage --exclude "/usr/*"
            VERBATIM
        )
        add_custom_target(collect_coverage
            COMMAND ${lcov} -c -d . -o test.info --branch-coverage --exclude "/usr/*"
            COMMAND ${lcov} -a base.info -a test.info -o all.info --branch-coverage
            COMMAND ${lcov} -r all.info "*/src/main.cc" -o coverage.info --branch-coverage
            COMMAND ${genhtml} coverage.info -o html --branch-coverage
            VERBATIM
        )
    else()
        message(WARNING "lcov or genhtml not found, coverage target will not be available")
    endif()

    enable_testing()

    find_package(Catch2 3 REQUIRED)
    find_path(TROMPELOEIL trompeloeil.hpp)
    if(NOT TROMPELOEIL)
        message(FATAL_ERROR "Trompeloeil not found, tests will not be built")
    endif()

    add_executable(tests tests/test.cc src/func.cc)
    target_include_directories(tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
    target_link_libraries(tests PRIVATE hello_compiler_flags Catch2::Catch2WithMain)
    
    add_test(NAME UnitTests COMMAND tests)
endif()
