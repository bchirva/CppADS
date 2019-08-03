#include <gtest/gtest.h>

#include "array.hpp"
using CppADS::Array;

TEST(ArrayTest, ConstructTest)
{
    Array<int> array_empty;
    ASSERT_EQ(array_empty.size(), 0);

    std::initializer_list<int> init_list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Array<int> array_init (init_list);
    auto list_it = init_list.begin();
    ASSERT_EQ(array_init.size(), init_list.size());
    for (auto it = array_init.begin(); it != array_init.end() && list_it != init_list.end(); ++it, ++list_it){
        ASSERT_EQ(*it, *list_it);
    }

    Array<int> array_copy (array_init);
    ASSERT_EQ(array_copy, array_init);

    Array<int> array_move (std::move(array_init));
    ASSERT_EQ(array_move, array_copy);
    ASSERT_EQ(array_init.size(), 0);
}

TEST(ArrayTest, IteratorsTest)
{
    Array<int> array_init {0,1,2,3,4,5,6,7,8,9};

    int value = 0;
    for(auto it = array_init.begin(); it != array_init.end(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }

    value = 0;
    for (auto it = array_init.cbegin(); it != array_init.cend(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }

    value = 9;
    for (auto it = array_init.rbegin(); it != array_init.rend(); ++it, value--) {
        ASSERT_EQ(*it, value);
    }
}

TEST(ArrayTest, FindTest)
{
    Array<int> array {0,11,22,33,44,55,66,77,88,99};
    auto item = array.find(22);
    auto end = array.find(-1);

    ASSERT_EQ(end, array.end());
    ASSERT_EQ(item, array.begin() + 2);
}

TEST(ArrayTest, AssignTest)
{
    std::initializer_list<int> init_list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Array<int> array_init (init_list);

    Array<int> array_copy;
    array_copy = array_init;
    ASSERT_EQ(array_copy, array_init);

    Array<int> array_move;
    array_move = std::move(array_init);
    ASSERT_EQ(array_move, array_copy);
    ASSERT_EQ(array_init.size(), 0);

    Array<int> non_equal {10,11,12,13,14,15};
    ASSERT_NE(non_equal, array_move);
}

TEST(ArrayTest, AccessTest)
{
    Array<int> array { 42, 1, 2, 3, 4, 5, 6, 7, 8, 69 };

    try {
        const int var = array[66];
        (void)(var);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::operator[]: index is out of range"));
    }

    array[5] = 50;
    int var = array[5];
    ASSERT_EQ(var, 50);
    ASSERT_EQ(array.front(), 42);
    ASSERT_EQ(array.back(), 69);
}

TEST(ArrayTest, InsertTest)
{
    Array<int> array {0, 1, 2, 3, 4, 5, 6, 7};
    int value { -11 };

    array.insert(value, 0);
    array.insert(100, array.begin());
    array.insert(9000, array.size());
    array.insert(1234, array.end());
    array.insert(789, 5);
    array.push_back(42);

    ASSERT_EQ(array, Array<int>({100, -11, 0, 1, 2, 789, 3, 4, 5, 6, 7, 9000, 1234, 42}));
    ASSERT_EQ(array.size(), 14);

    try {
        array.insert(42, 666);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::insert: index is out of range"));
    }
    try {
        array.insert(42, array.begin() - 666);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::insert: iterator is invalid"));
    }

}

TEST(ArrayTest, RemoveTest)
{
    Array<int> array {0, 1, 2, 3, 4, 5, 6, 7, 8};

    array.remove(3);
    array.remove(array.begin() + 2);
    array.remove(array.begin());
    array.remove(--array.end());
    array.pop_back();

    ASSERT_EQ(array, Array<int>({1,4,5,6}));
    ASSERT_EQ(array.size(), 4);

    array.clear();
    ASSERT_EQ(array.size(), 0);

    try {
        array.remove(66);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::remove: index is out of range"));
    }

    try {
        array.remove(array.begin() - 99);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::Array<T>::remove: iterator is invalid"));
    }
}

TEST(ArrayTest, CapacityTest)
{
    Array<int> array;
    ASSERT_EQ(array.capacity(), 0);

    for (int i = 0; i < 128; i++)
    {
        array.insert(i, array.end());
        size_t expected_capacity = std::pow(2, std::ceil(std::log2(array.size())));
        ASSERT_EQ(array.capacity(), expected_capacity);
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
