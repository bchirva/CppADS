cmake_minimum_required(VERSION 3.10)

project(CppADS
    VERSION 0.1
    DESCRIPTION "C++ implementation of algorithms and data structures"
)

add_library(CppADS INTERFACE)
add_library(CppADS::CppADS ALIAS CppADS)

target_include_directories(CppADS INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

#FILE(GLOB SOURCE_CPP ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
#target_sources(CppADS PRIVATE ${SOURCE_CPP})

target_compile_features(CppADS INTERFACE cxx_std_14)

set(WITH_TESTS OFF CACHE BOOL "Is tests builds required")
set(WITH_DOCS  OFF CACHE BOOL "Is documentation build required")

if(WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(WITH_DOCS)
    add_subdirectory(docs)
endif()
