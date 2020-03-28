#include <gtest/gtest.h>

#include <deque.hpp>
using CppADS::Deque;

TEST(DequeTest, ConstructDequeTest)
{
    Deque<int> deque_empty;
    ASSERT_EQ(deque_empty.size(), 0);

    Deque<int> deque_init {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(deque_init.size(), 10);

    Deque<int> deque_copy(deque_init);
    ASSERT_EQ(deque_copy, deque_init);

    Deque<int> deque_move(std::move(deque_init));
    ASSERT_EQ(deque_move, deque_copy);
    ASSERT_EQ(deque_init.size(), 0);
}

TEST(DequeTest, AssignDequeTest)
{
    Deque<int> deque_init { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto init_size = deque_init.size();

    Deque<int> deque_copy;
    deque_copy = deque_init;
    ASSERT_EQ(deque_copy.size(), init_size);

    Deque<int> deque_move;
    deque_move = std::move(deque_init);
    ASSERT_EQ(deque_move.size(), init_size);
    ASSERT_EQ(deque_init.size(), 0);
}

TEST(DequeTest, ModifyDequeTest)
{
    Deque<int> deque;
    for (int i = 100; i > 0; i--)
    {
        deque.push_front(i);
        deque.push_back(i);
    }

    ASSERT_EQ(deque.size(), 200);
    ASSERT_EQ(deque.front(), 1);
    ASSERT_EQ(deque.back(), 1);

    while(deque.size() > 50)
    {
        deque.pop_back();
        deque.pop_front();
    }

    ASSERT_EQ(deque.size(), 50);
    ASSERT_EQ(deque.front(), 76);
    ASSERT_EQ(deque.back(), 76);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
