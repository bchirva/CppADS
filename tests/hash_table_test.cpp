#include <gtest/gtest.h>

#include "hash_table.hpp"
using CppADS::HashTable;

TEST (HashTableTest, ContructTest)
{
    HashTable<int, int> empty;
    ASSERT_EQ(empty.size(), 0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
