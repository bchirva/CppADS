#include <gtest/gtest.h>

#include "list.hpp"
using CppADS::List;

TEST(ListTest, ConstructTest)
{
    List<int> list_empty;
    ASSERT_EQ(list_empty.size(), 0);
    ASSERT_EQ(list_empty.begin(), list_empty.end());

    std::initializer_list<int> init_list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    List<int> list_init (init_list);
    ASSERT_EQ(list_init.size(), init_list.size());
    auto list_it = init_list.begin();
    for (auto it = list_init.begin(); it != list_init.end() && list_it != init_list.end(); ++it, ++list_it) {
        ASSERT_EQ(*it, *list_it);
    }

    List<int> list_copy (list_init);
    ASSERT_EQ(list_copy, list_init);

    List<int> list_move (std::move(list_init));
    ASSERT_EQ(list_move, list_copy);
    ASSERT_EQ(list_init.size(), 0);
}

TEST(ListTest, AssignTest)
{
    List<int> list_init { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    List<int> list_copy;
    list_copy = list_init;
    ASSERT_EQ(list_copy, list_init);

    List<int> list_move;
    list_move = std::move(list_init);
    ASSERT_EQ(list_move, list_copy);
    ASSERT_EQ(list_init.size(), 0);
}

TEST(ListTest, IteratorsTest)
{
    List<int> list_init {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int value = 0;
    for(auto it = list_init.begin(); it != list_init.end(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }

    value = 0;
    for (auto it = list_init.cbegin(); it != list_init.cend(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }

    value = 9;
    for (auto it = list_init.rbegin(); it != list_init.rend(); ++it, value--) {
        ASSERT_EQ(*it, value);
    }
}

TEST(ListTest, FindTest)
{
    List<int> list {0,11,22,33,44,55,66,77,88,99};
    auto item = list.find(22);
    auto end = list.find(-1);

    ASSERT_EQ(end, list.end());
    ASSERT_EQ(item, (list.begin()++)++);
}

TEST(ListTest, AccessTest)
{
    List<int> list { 42, 1, 2, 3, 4, 5, 6, 7, 8, 69 };

    list[5] = 50;
    int var = list[5];
    ASSERT_EQ(var, 50);
    ASSERT_EQ(list.front(), 42);
    ASSERT_EQ(list.back(), 69);

    ASSERT_THROW(list[66], std::out_of_range);
}

TEST(ListTest, InsertTest)
{
    List<int> list {0, 1, 2, 3, 4, 5, 6, 7};
    int value { -11 };

    list.push_front(value);
    list.insert(100, list.begin());
    list.push_back(9000);
    list.insert(1234, list.end());
    list.insert(789, list.find(3));

    ASSERT_EQ(list, List<int>({100, -11, 0, 1, 2, 789, 3, 4, 5, 6, 7, 9000, 1234}));
    ASSERT_EQ(list.size(), 13);

    list.clear();
    for (int i = 1; i < 100; i += 10)
        list.push_front(i);
    ASSERT_EQ(list, List<int>({91, 81, 71, 61, 51, 41, 31, 21, 11, 1}));

    list.clear();
    for (int i = 1; i < 100; i += 10)
        list.push_back(i);
    ASSERT_EQ(list, List<int>({1, 11, 21, 31, 41, 51, 61, 71, 81, 91}));
}

TEST(ListTest, RemoveTest)
{
    List<int> list {0, 1, 2, 3, 4, 5, 6, 7};

    list.remove(list.find(3));
    list.remove(list.begin());
    list.remove(--list.end());
    list.pop_back();
    list.pop_front();

    ASSERT_EQ(list, List<int>({2,4,5}));
    ASSERT_EQ(list.size(), 3);

    list.clear();
    ASSERT_EQ(list.size(), 0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
