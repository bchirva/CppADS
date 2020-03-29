#include <gtest/gtest.h>

#include "hash_table.hpp"
using CppADS::HashTable;

TEST (HashTableTest, ContructTest)
{
    HashTable<int, int> empty;
    ASSERT_EQ(empty.size(), 0);

    HashTable<const char*, int> hash_init {std::make_pair("111", 1), std::make_pair("222", 2),
                                           std::make_pair("333", 3), std::make_pair("444", 4),
                                           std::make_pair("555", 5), std::make_pair("666", 6),
                                           std::make_pair("777", 7), std::make_pair("888", 8),
                                           std::make_pair("999", 9), std::make_pair("000", 0)};

   ASSERT_EQ(hash_init.size(), 10);

   HashTable<const char*, int> hash_copy(hash_init);
   ASSERT_EQ(hash_init, hash_copy);

   HashTable<const char*, int> hash_move(std::move(hash_init));
   ASSERT_EQ(hash_copy, hash_move);
   ASSERT_EQ(hash_init.size(), 0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
