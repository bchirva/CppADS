#include <gtest/gtest.h>

#include "forward_list.hpp"
using CppADS::ForwardList;

TEST (ForwardListTest, ContructTest)
{
    ForwardList<int> empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty.begin(), empty.end());

    std::initializer_list<int> init_list {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ForwardList<int> list_init (init_list);
    ASSERT_EQ(list_init.size(), init_list.size());
    auto list_it = init_list.begin();
    for (auto it = list_init.begin(); it != list_init.end() && list_it != init_list.end(); ++it, ++list_it) {
        ASSERT_EQ(*it, *list_it);
    }

    ForwardList<int> list_copy (list_init);
    ASSERT_EQ(list_init, list_copy);

    ForwardList<int> list_move (std::move(list_init));
    ASSERT_EQ(list_copy, list_move);
    ASSERT_EQ(list_init.size(), 0);
}

TEST(ForwardListTest, AssignTest)
{
    ForwardList<int> list_init { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    ForwardList<int> list_copy;
    list_copy = list_init;
    ASSERT_EQ(list_copy, list_init);

    ForwardList<int> list_move;
    list_move = std::move(list_init);
    ASSERT_EQ(list_move, list_copy);
    ASSERT_EQ(list_init.size(), 0);
}

TEST(ForwardListTest, IteratorsTest)
{
    ForwardList<int> list_init {0,1,2,3,4,5,6,7,8,9};

    int value = 0;
    for(auto it = list_init.begin(); it != list_init.end(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }

    value = 0;
    for (auto it = list_init.cbegin(); it != list_init.cend(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }
}

TEST(ForwardListTest, FindTest)
{
    ForwardList<int> list {0,11,22,33,44,55,66,77,88,99};
    auto item = list.find(22);
    auto end = list.find(-1);

    ASSERT_EQ(end, list.end());
    auto third = (list.begin()++)++;
    ASSERT_EQ(item, third);
}

TEST(ForwardListTest, AccessTest)
{
    ForwardList<int> list { 42, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    list[5] = 50;
    int var = list[5];
    ASSERT_EQ(var, 50);
    ASSERT_EQ(list.front(), 42);

    ASSERT_THROW(list[66], std::out_of_range);

}

TEST(ForwardListTest, InsertTest)
{
    ForwardList<int> list {0, 1, 2, 3, 4, 5, 6, 7};
    int value { -11 };

    list.push_front(value);
    list.push_front(100);
    list.push_back(9000);
    list.push_back(1234);
    list.insert_after(789, list.find(2));
    list.insert_after(17, list.before_begin());

    ASSERT_EQ(list, ForwardList<int>({17, 100, -11, 0, 1, 2, 789, 3, 4, 5, 6, 7, 9000, 1234}));
    ASSERT_EQ(list.size(), 14);

    list.clear();
    for (int i = 1; i < 100; i += 10)
        list.push_front(i);
    ASSERT_EQ(list, ForwardList<int>({91, 81, 71, 61, 51, 41, 31, 21, 11, 1}));

    list.clear();
    for (int i = 1; i < 100; i += 10)
        list.push_back(i);
    ASSERT_EQ(list, ForwardList<int>({1, 11, 21, 31, 41, 51, 61, 71, 81, 91}));
}

TEST(ForwardListTest, RemoveTest)
{
    ForwardList<int> list {0, 1, 2, 3, 4, 5, 6, 7};

    list.remove_after(list.find(2));
    list.remove_after(list.begin()++);
    list.pop_front();

    ASSERT_EQ(list, ForwardList<int>({1,4,5,6,7}));
    ASSERT_EQ(list.size(), 5);

    list.clear();
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.begin(), list.end());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
