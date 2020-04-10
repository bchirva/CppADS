#include <gtest/gtest.h>
#include "hash_table.hpp"
using CppADS::HashTable;

enum class TestEnum : uint8_t {
    A = 0x1, B = 0x2, C = 0x4, D = 0x8, E = 0x10, F = 0x20, G = 0x40, H = 0x80, I, J, None = 0x0, Last = 0xFF
};

TEST (HashTableTest, ContructTest)
{
    HashTable<int, int> empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_EQ(empty.begin(), empty.end());

    std::initializer_list<std::pair<std::string, int>> init_list {
        {"111", 1}, {"222", 2}, {"333", 3}, {"444", 4}, {"555", 5}, {"666", 6}, {"777", 7}, {"888", 8}, {"999", 9}, {"000", 0}};

    HashTable<std::string, int> hash_init (init_list);
    ASSERT_EQ(hash_init.size(), init_list.size());

    HashTable<std::string, int> hash_copy(hash_init);
    ASSERT_EQ(hash_init, hash_copy);

    HashTable<std::string, int> hash_move(std::move(hash_init));
    ASSERT_EQ(hash_copy, hash_move);
    ASSERT_EQ(hash_init.size(), 0);
}

TEST (HashTableTest, AssignTest)
{
    HashTable<std::string, int> hash_init {{"aaa", 101}, {"bbb", 202}, {"ccc", 303}, {"ddd", 404},
                                           {"eee", 505}, {"fff", 606}, {"ggg", 707}, {"hhh", 808}};

    HashTable<std::string, int> hash_copy;
    hash_copy = hash_init;
    ASSERT_EQ(hash_init, hash_copy);

    HashTable<std::string, int> hash_move;
    hash_move = std::move(hash_init);
    ASSERT_EQ(hash_copy, hash_move);
    ASSERT_EQ(hash_init.size(), 0);

}

/*
/// \todo Implement this test case
TEST (HashTableTest, IteratorTest)
{}
*/

TEST (HashTableTest, FindTest)
{
    HashTable<TestEnum, int> hash {{TestEnum::A, 101}, {TestEnum::B, 202}, {TestEnum::C, 303}, {TestEnum::D, 404},
                                   {TestEnum::E, 505}, {TestEnum::F, 606}, {TestEnum::G, 707}, {TestEnum::H, 808}};

    ASSERT_EQ(*(hash.find(TestEnum::C)), decltype(hash)::value_type({TestEnum::C, 303}));
    ASSERT_EQ(hash.find(TestEnum::None), hash.end());
}

TEST (HashTableTest, AccessTest)
{
    HashTable<TestEnum, int> hash {{TestEnum::A, 101}, {TestEnum::B, 202}, {TestEnum::C, 303}, {TestEnum::D, 404},
                                   {TestEnum::E, 505}, {TestEnum::F, 606}, {TestEnum::G, 707}, {TestEnum::H, 808}};

    ASSERT_EQ(hash[TestEnum::A], 101);
    ASSERT_EQ(hash[TestEnum::None], int());

    hash[TestEnum::I] = 111;
    ASSERT_EQ(hash[TestEnum::I], 111);
    hash[TestEnum::F] = 0xFFFF;
    ASSERT_EQ(hash[TestEnum::F], 0xFFFF);

    ASSERT_EQ(hash, decltype(hash)({{TestEnum::A, 101}, {TestEnum::B, 202}, {TestEnum::C, 303}, {TestEnum::D, 404},
                                    {TestEnum::E, 505}, {TestEnum::G, 707}, {TestEnum::H, 808}, {TestEnum::I, 111},
                                    {TestEnum::F, 0xFFFF}, {TestEnum::None, int()}}));

}

TEST (HashTableTest, InsertTest)
{
    HashTable<char, int> hash {{'a', 1}, {'b', 2}, {'c', 3}, {'x', 100}, {'y', 200}, {'z', 300}};

    hash.insert({'R', 501});
    std::pair<char, int> pair {'a', 10000};
    hash.insert(pair);
    pair = std::make_pair('v', 5);
    hash.insert(std::move(pair));

    ASSERT_EQ(hash, decltype(hash)({{'a', 10000}, {'b', 2}, {'c', 3}, {'x', 100}, {'y', 200}, {'z', 300}, {'R', 501}, {'v', 5}}));
    ASSERT_EQ(hash.size(), 8);
}

TEST (HashTableTest, RemoveTest)
{
    HashTable<char, int> hash {{'a', 1}, {'b', 2}, {'c', 3}, {'x', 100}, {'y', 200}, {'z', 300}, {'R', 501}, {'j', 10000}, {'v', 5}};
    hash.remove('y');
    hash.remove('b');
    hash.remove('j');

    ASSERT_EQ(hash, decltype(hash)({{'a', 1}, {'c', 3}, {'x', 100}, {'z', 300}, {'R', 501}, {'v', 5}}));
    ASSERT_EQ(hash.size(), 6);

    hash.clear();
    ASSERT_EQ(hash.size(), 0);
    ASSERT_EQ(hash.bucket_count(), 1);
    ASSERT_EQ(hash.begin(), hash.end());
}

/*
/// \todo Implement this test case
TEST (HashTableTest, CapacityTest)
{}
*/

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
