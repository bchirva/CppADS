find_package(GTest QUIET)

if (GTest_FOUND)
    enable_testing()

    add_executable(ArrayTest ArrayTest.cpp)
    target_link_libraries(ArrayTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(ArrayTest "ArrayTest")

    add_executable(ForwardListTest ForwardListTest.cpp)
    target_link_libraries(ForwardListTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(ForwardListTest "ForwardListTest")

    add_executable(ListTest ListTest.cpp)
    target_link_libraries(ListTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(ListTest "ListTest")

    add_executable(StackTest StackTest.cpp)
    target_link_libraries(StackTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(StackTest "StackTest")

    add_executable(QueueTest QueueTest.cpp)
    target_link_libraries(QueueTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(QueueTest "QueueTest")

    add_executable(DequeTest DequeTest.cpp)
    target_link_libraries(DequeTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(DequeTest "DequeTest")

    message("Tests build has configured")
else()
    message(WARNING "GoogleTest not found. Tests hasn't configured")
endif()
