#include <gtest/gtest.h>

#include "Stack.hpp"

using CppADS::Stack;

TEST(StackTest, ConstructTest)
{
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

TEST(StackTest, IteratorTest)
{
    Stack<int> it_stack;
    for (int i = 0; i < 32; i++)
        it_stack.push(i);

    Stack<int> compare_stack(it_stack);

    for (auto it = it_stack.begin(); it != it_stack.end(); it++)
    {
        ASSERT_EQ(*it, compare_stack.top());
        compare_stack.pop();
    }
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
