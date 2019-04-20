#include <gtest/gtest.h>

#include "Array.hpp"
using CppADS::Array;

TEST(ArrayTest, ConstructArrayTest)
{
    Array<int> array_empty;
    ASSERT_EQ(array_empty.size(), 0);

    std::initializer_list<int> init_list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Array<int> array_init (init_list);
    ASSERT_EQ(array_init.size(), init_list.size());

    Array<int> array_copy (array_init);
    ASSERT_EQ(array_copy.size(), init_list.size());
    
    Array<int> array_move (std::move(array_init));
    ASSERT_EQ(array_move.size(), init_list.size());
    ASSERT_EQ(array_init.size(), 0);
}

TEST(ArrayTest, AssignArrayTest)
{
    std::initializer_list<int> init_list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Array<int> array_init (init_list);

    Array<int> array_copy;
    array_copy = array_init;
    ASSERT_EQ(array_copy.size(), init_list.size());
    
    Array<int> array_move;
    array_move = std::move(array_init);
    ASSERT_EQ(array_move.size(), init_list.size());
    ASSERT_EQ(array_init.size(), 0);
}

TEST(ArrayTest, AccessTest)
{
    Array<int> array { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    try {
        const int var = array[66];
        (void)(var);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::operator[]: index is out of range"));
    }

    array[5] = 50;
    int var = array[5];
    ASSERT_EQ(var, 50);
}

TEST(ArrayTest, InsertTest)
{
    Array<int> array {0, 1, 2, 3, 4, 5, 6, 7};
    int value { 3 };
    array.insert(value, 3);
    array.insert(100, 0);
    array.insert(9000, array.size());

    try {
        array.insert(42, 666);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::insert: index is out of range"));
    }

    ASSERT_EQ(array[0], 100);
    ASSERT_EQ(array[4], value);
    ASSERT_EQ(array[array.size() - 1], 9000);
    ASSERT_EQ(array.size(), 11);
}

TEST(ArrayTest, RemoveTest)
{
    Array<int> array {0, 1, 2, 3, 4, 5, 6, 7};

    array.remove(3);
    ASSERT_EQ(array[3], 4);
    array.remove(0, 2);
    ASSERT_EQ(array[2], 5);
    array.remove(array.size() - 1);
    ASSERT_EQ(array[array.size() - 1], 6);
    ASSERT_EQ(array.size(), 4);

    try {
        array.remove(66);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::remove: index is out of range"));
    }

    try {
        array.remove(0, 66);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::remove: count is out of range"));
    }

    array.clear();
    ASSERT_EQ(array.size(), 0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
