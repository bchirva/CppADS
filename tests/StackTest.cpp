#include <gtest/gtest.h>

#include "Stack.hpp"

using CppADS::Stack;

TEST(StackTest, ConstructStackTest)
{
    Stack<int> stack_init {0,1,2,3,4,5,6};
    ASSERT_EQ(stack_init.size(), 7);

    Stack<int> stack_copy(stack_init);
    ASSERT_EQ(stack_copy.size(), 7);

    Stack<int> stack_move(std::move(stack_init));
    ASSERT_EQ(stack_move.size(), 7);

    while(stack_copy.size() && stack_move.size())
    {
        int copy_value = stack_copy.pop();
        int move_value = stack_move.pop();
        ASSERT_EQ(copy_value, move_value);
    }
    ASSERT_EQ(stack_copy.size(), 0);
    ASSERT_EQ(stack_move.size(), 0);
}

TEST(StackTest, AssignStackTest)
{

}

TEST(StackTest, ModifyStackTest)
{

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
