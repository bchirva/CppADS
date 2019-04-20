find_package(GTest QUIET)

if (GTest_FOUND)

add_executable(ArrayTest ArrayTest.cpp)
target_link_libraries(ArrayTest PRIVATE GTest::GTest CppADS::CppADS)

add_test(ArrayTest "ArrayTest")

endif()
