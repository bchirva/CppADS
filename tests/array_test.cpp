#include <gtest/gtest.h>

#include "array.hpp"
using CppADS::Array;

TEST(ArrayTest, ConstructTest)
{
    Array<int> array_empty;
    ASSERT_EQ(array_empty.size(), 0);
    ASSERT_EQ(array_empty.begin(), array_empty.end());

    std::initializer_list<int> init_list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Array<int> array_init(init_list);
    ASSERT_EQ(array_init.size(), init_list.size());
    auto list_it = init_list.begin();
    for (auto it = array_init.begin(); it != array_init.end() && list_it != init_list.end();
         ++it, ++list_it)
    {
        ASSERT_EQ(*it, *list_it);
    }

    Array<int> array_copy(array_init);
    ASSERT_EQ(array_copy, array_init);

    Array<int> array_move(std::move(array_init));
    ASSERT_EQ(array_copy, array_move);
    ASSERT_EQ(array_init.size(), 0);
}

TEST(ArrayTest, AssignTest)
{
    Array<int> array_init{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Array<int> array_copy;
    array_copy = array_init;
    ASSERT_EQ(array_copy, array_init);

    Array<int> array_move;
    array_move = std::move(array_init);
    ASSERT_EQ(array_move, array_copy);
    ASSERT_EQ(array_init.size(), 0);
}

TEST(ArrayTest, IteratorsTest)
{
    Array<int> array_init{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    int value = 0;
    for (auto it = array_init.begin(); it != array_init.end(); ++it, value++)
    {
        ASSERT_EQ(*it, value);
    }

    value = 0;
    for (auto it = array_init.cbegin(); it != array_init.cend(); ++it, value++)
    {
        ASSERT_EQ(*it, value);
    }

    value = 9;
    for (auto it = array_init.rbegin(); it != array_init.rend(); ++it, value--)
    {
        ASSERT_EQ(*it, value);
    }
}

TEST(ArrayTest, FindTest)
{
    Array<int> array{ 0, 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    auto item = array.find(22);
    auto end = array.find(-1);

    ASSERT_EQ(end, array.end());
    ASSERT_EQ(item, array.begin() + 2);
}

TEST(ArrayTest, AccessTest)
{
    Array<int> array{ 42, 1, 2, 3, 4, 5, 6, 7, 8, 69 };

    array[5] = 50;
    int var = array[5];
    ASSERT_EQ(var, 50);
    ASSERT_EQ(array.front(), 42);
    ASSERT_EQ(array.back(), 69);

    ASSERT_THROW(array[66], std::out_of_range);
}

TEST(ArrayTest, InsertTest)
{
    Array<int> array{ 0, 1, 2, 3, 4, 5, 6, 7 };
    int value{ -11 };

    array.insert(value, 0);
    array.insert(100, array.begin());
    array.insert(9000, array.size());
    array.insert(1234, array.end());
    array.insert(789, 5);
    array.push_back(42);
    array.push_front(1234);

    ASSERT_EQ(array, Array<int>({ 1234, 100, -11, 0, 1, 2, 789, 3, 4, 5, 6, 7, 9000, 1234, 42 }));
    ASSERT_EQ(array.size(), 15);

    array.clear();
    for (int i = 1; i < 100; i += 10)
        array.push_back(i);
    ASSERT_EQ(array, Array<int>({ 1, 11, 21, 31, 41, 51, 61, 71, 81, 91 }));

    array.clear();
    for (int i = 1; i < 100; i += 10)
        array.push_front(i);
    ASSERT_EQ(array, Array<int>({ 91, 81, 71, 61, 51, 41, 31, 21, 11, 1 }));

    ASSERT_THROW(array.insert(42, 666), std::out_of_range);
    ASSERT_THROW(array.insert(42, array.begin() - 666), std::out_of_range);
}

TEST(ArrayTest, RemoveTest)
{
    Array<int> array{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    array.remove(3);
    array.remove(array.begin() + 2);
    array.remove(array.begin());
    array.remove(--array.end());
    array.pop_back();
    array.pop_front();

    ASSERT_EQ(array, Array<int>({ 4, 5, 6 }));
    ASSERT_EQ(array.size(), 3);

    array.clear();
    ASSERT_EQ(array.size(), 0);

    ASSERT_THROW(array.remove(66), std::out_of_range);
    ASSERT_THROW(array.remove(array.begin() - 99), std::out_of_range);
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
