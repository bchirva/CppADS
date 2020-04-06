#include <gtest/gtest.h>

#include "hash_table.hpp"
using CppADS::HashTable;

TEST (HashTableTest, ContructTest)
{
    HashTable<int, int> empty;
    ASSERT_EQ(empty.size(), 0);

    std::initializer_list<std::pair<const char*, int>> init_list {std::make_pair("111", 1), std::make_pair("222", 2),
                                                                  std::make_pair("333", 3), std::make_pair("444", 4),
                                                                  std::make_pair("555", 5), std::make_pair("666", 6),
                                                                  std::make_pair("777", 7), std::make_pair("888", 8),
                                                                  std::make_pair("999", 9), std::make_pair("000", 0)};

    HashTable<const char*, int> hash_init (init_list);
    ASSERT_EQ(hash_init.size(), init_list.size());

    HashTable<const char*, int> hash_copy(hash_init);
    ASSERT_EQ(hash_init, hash_copy);

    HashTable<const char*, int> hash_move(std::move(hash_init));
    ASSERT_EQ(hash_copy, hash_move);
    ASSERT_EQ(hash_init.size(), 0);
}

TEST (HashTableTest, AssignTest)
{
    HashTable<const char*, int> hash_init {{"aaa", 101}, {"bbb", 202}, {"ccc", 303}, {"ddd", 404},
                                           {"eee", 505}, {"fff", 606}, {"ggg", 707}, {"hhh", 808}};

    HashTable<const char*, int> hash_copy;
    hash_copy = hash_init;
    ASSERT_EQ(hash_init, hash_copy);

    HashTable<const char*, int> hash_move;
    hash_move = std::move(hash_init);
    ASSERT_EQ(hash_copy, hash_move);
    ASSERT_EQ(hash_init.size(), 0);

}

TEST (HashTableTest, IteratorTest)
{
//    HashTable<int, int> hash {{1, 101}, {2, 202}, {3, 303}, {4, 404}, {5, 505}, {6,606}, {7,707}, {8,808}, {9,909}, {10, 1010}};
}

TEST (HashTableTest, FindTest)
{

}

TEST (HashTableTest, AccessTest)
{

}

TEST (HashTableTest, InsertTest)
{
    HashTable<char, int> hash {{'a', 1}, {'b', 2}, {'c', 3}, {'x', 100}, {'y', 200}, {'z', 300}};

    hash.insert({'R', 501});
    std::pair<char, int> pair {'j', 10000};
    hash.insert(pair);
    pair = std::make_pair('v', 5);
    hash.insert(std::move(pair));

    ASSERT_EQ(hash, decltype(hash)({{'a', 1}, {'b', 2}, {'c', 3}, {'x', 100}, {'y', 200}, {'z', 300}, {'R', 501}, {'j', 10000}, {'v', 5}}));
    ASSERT_EQ(hash.size(), 9);
}

TEST (HashTableTest, RemoveTest)
{
    HashTable<char, int> hash {{'a', 1}, {'b', 2}, {'c', 3}, {'x', 100}, {'y', 200}, {'z', 300}, {'R', 501}, {'j', 10000}, {'v', 5}};
    hash.remove('y');
    hash.remove('b');
    hash.remove('j');

    ASSERT_EQ(hash, decltype(hash)({{'a', 1}, {'c', 3}, {'x', 100}, {'z', 300}, {'R', 501}, {'v', 5}}));
}

TEST (HashTableTest, CapacityTest)
{

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
