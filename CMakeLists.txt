cmake_minimum_required(VERSION 3.10)

project(hello VERSION 0.1)

add_library(hello_compiler_flags INTERFACE)
target_compile_features(hello_compiler_flags INTERFACE cxx_std_11)
target_compile_options(hello_compiler_flags INTERFACE 
    "-Wall;-Wextra;-Wpedantic"
    "$<$<CONFIG:Debug>:-O0;-coverage>"
)

add_executable(hello src/main.cpp src/func.cpp)

target_link_libraries(hello PUBLIC hello_compiler_flags)
target_link_options(hello PUBLIC
    "$<$<CONFIG:Debug>:-coverage>"
)

find_program(prog_gcov gcov)
find_program(prog_lcov lcov)

if(prog_gcov AND prog_lcov)
    message(STATUS "gcov found: ${prog_gcov}")
    message(STATUS "lcov found: ${prog_lcov}")

    add_custom_target(collect_coverage_init
        COMMAND ${prog_lcov} -i -c -d . -o base.info --branch-coverage
        VERBATIM
    )
    add_custom_target(collect_coverage
        COMMAND ${prog_gcov} main.cpp.o -b -o CMakeFiles/hello.dir/src # hello を実行した時のカバレッジ
        COMMAND ${prog_gcov} func.cpp.o -b -o CMakeFiles/tests.dir/src # tests を実行した時のカバレッジ
        COMMAND ${prog_gcov} test.cpp.o -b -o CMakeFiles/tests.dir/tests # tests を実行した時のカバレッジ
        COMMAND ${prog_lcov} -c -d . -o test.info --branch-coverage
        COMMAND ${prog_lcov} -a base.info -a test.info -o coverage.info --branch-coverage --exclude "/usr/*"
        VERBATIM
    )
else()
    message(WARNING "gcov or lcov not found, coverage target will not be available")
endif()

enable_testing()

add_test(NAME Runs COMMAND hello)

find_package(Catch2 3 REQUIRED)

add_executable(tests tests/test.cpp src/func.cpp)
target_include_directories(tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(tests PUBLIC Catch2::Catch2WithMain hello_compiler_flags)
target_link_options(tests PUBLIC
    "$<$<CONFIG:Debug>:-coverage>"
)

add_test(NAME UnitTests COMMAND tests)
