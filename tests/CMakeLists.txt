find_package(GTest QUIET)

if (GTest_FOUND)
    add_executable(ArrayTest array_test.cpp)
    target_link_libraries(ArrayTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(ArrayTest "ArrayTest")

    add_executable(ForwardListTest forward_list_test.cpp)
    target_link_libraries(ForwardListTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(ForwardListTest "ForwardListTest")

    add_executable(ListTest list_test.cpp)
    target_link_libraries(ListTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(ListTest "ListTest")

    add_executable(StackTest stack_test.cpp)
    target_link_libraries(StackTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(StackTest "StackTest")

    add_executable(QueueTest queue_test.cpp)
    target_link_libraries(QueueTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(QueueTest "QueueTest")

    add_executable(DequeTest deque_test.cpp)
    target_link_libraries(DequeTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(DequeTest "DequeTest")

    add_executable(HashTableTest hash_table_test.cpp)
    target_link_libraries(HashTableTest PRIVATE GTest::GTest CppADS::CppADS)
    add_test(HashTableTest "HashTableTest")

    message("Tests build has configured")
else()
    message(WARNING "GoogleTest not found. Tests hasn't configured")
endif()
