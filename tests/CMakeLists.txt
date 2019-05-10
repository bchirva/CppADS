find_package(GTest QUIET)

if (GTest_FOUND)

add_executable(ArrayTest ArrayTest.cpp)
target_link_libraries(ArrayTest PRIVATE GTest::GTest CppADS::CppADS)

add_executable(StackTest StackTest.cpp)
target_link_libraries(StackTest PRIVATE GTest::GTest CppADS::CppADS)

add_executable(QueueTest QueueTest.cpp)
target_link_libraries(QueueTest PRIVATE GTest::GTest CppADS::CppADS)

add_test(ArrayTest "ArrayTest")
add_test(StackTest "StackTest")
add_test(QueueTest "QueueTest")
endif()
