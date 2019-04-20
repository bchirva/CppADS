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

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
