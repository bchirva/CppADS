find_package(GTest QUIET)

if (GTest_FOUND)

add_executable(ArrayTest ArrayTest.cpp)
target_link_libraries(ArrayTest PRIVATE GTest::GTest CppADS::CppADS)
add_test(ArrayTest "ArrayTest")

add_executable(ForwardListTest ForwardListTest.cpp)
target_link_libraries(ForwardListTest PRIVATE GTest::GTest CppADS::CppADS)
add_test(ForwardListTest "ForwardListTest")

add_executable(StackTest StackTest.cpp)
target_link_libraries(StackTest PRIVATE GTest::GTest CppADS::CppADS)
add_test(StackTest "StackTest")

add_executable(QueueTest QueueTest.cpp)
target_link_libraries(QueueTest PRIVATE GTest::GTest CppADS::CppADS)
add_test(QueueTest "QueueTest")

add_executable(DequeTest DequeTest.cpp)
target_link_libraries(DequeTest PRIVATE GTest::GTest CppADS::CppADS)
add_test(DequeTest "DequeTest")

endif()
