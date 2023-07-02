cmake_minimum_required(VERSION 3.12)

project(
        lab11
        VERSION 1.0
        DESCRIPTION "C++ YEAR 2023 Lab11"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(bin)
add_subdirectory(lib)

enable_testing()
add_subdirectory(tests)