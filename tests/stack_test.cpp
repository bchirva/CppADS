#include <gtest/gtest.h>

#include "stack.hpp"
using CppADS::Stack;

TEST(StackTest, ConstructTest)
{
    Stack<int> stack_empty;
    ASSERT_EQ(stack_empty.size(), 0);

    Stack<int> stack_init {0,1,2,3,4,5,6};
    ASSERT_EQ(stack_init.size(), 7);

    Stack<int> stack_copy(stack_init);
    ASSERT_EQ(stack_copy.size(), 7);

    Stack<int> stack_move(std::move(stack_init));
    ASSERT_EQ(stack_move.size(), 7);

    while(stack_copy.size() && stack_move.size())
    {
        int copy_value = stack_copy.top();
        int move_value = stack_move.top();
        ASSERT_EQ(copy_value, move_value);
        stack_copy.pop();
        stack_move.pop();
    }
    ASSERT_EQ(stack_copy.size(), 0);
    ASSERT_EQ(stack_move.size(), 0);
}

TEST(StackTest, AssignTest)
{
    Stack<int> stack_init {0,1,2,3,4,5,6};
    ASSERT_EQ(stack_init.size(), 7);

    Stack<int> stack_copy;
    stack_copy = stack_init;
    ASSERT_EQ(stack_copy.size(), 7);

    Stack<int> stack_move;
    stack_move = std::move(stack_init);
    ASSERT_EQ(stack_move.size(), 7);

    while(stack_copy.size() && stack_move.size())
    {
        int copy_value = stack_copy.top();
        int move_value = stack_move.top();
        ASSERT_EQ(copy_value, move_value);
        stack_copy.pop();
        stack_move.pop();
    }
    ASSERT_EQ(stack_copy.size(), 0);
    ASSERT_EQ(stack_move.size(), 0);
}

TEST(StackTest, ModifyTest)
{
    Stack<int> stack;
    for (int i = 0; i < 100; i++)
        stack.push(i);

    ASSERT_EQ(stack.size(), 100);
    ASSERT_EQ(stack.top(), 99);

    while(stack.size() > 50)
        stack.pop();

    ASSERT_EQ(stack.size(), 50);
    ASSERT_EQ(stack.top(), 49);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
