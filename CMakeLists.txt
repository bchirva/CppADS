cmake_minimum_required(VERSION 3.10)

project(CppADS)

add_library(CppADS INTERFACE)
add_library(CppADS::CppADS ALIAS CppADS)

target_include_directories(CppADS INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )

target_compile_features(CppADS INTERFACE cxx_std_14)

enable_testing()
add_subdirectory(tests)
