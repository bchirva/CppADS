#include <gtest/gtest.h>

#include "List.hpp"
using CppADS::List;

TEST(ListTest, ConstructTest)
{
    List<int> list_empty;
    ASSERT_EQ(list_empty.size(), 0);

    std::initializer_list<int> init_list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    List<int> list_init (init_list);
    auto list_it = init_list.begin();
    ASSERT_EQ(list_init.size(), init_list.size());
    for (auto it = list_init.begin(); it != list_init.end() && list_it != init_list.end(); ++it, ++list_it){
        ASSERT_EQ(*it, *list_it);
    }

    List<int> list_copy (list_init);
    ASSERT_EQ(list_copy, list_init);

    List<int> list_move (std::move(list_init));
    ASSERT_EQ(list_move, list_copy);
    ASSERT_EQ(list_init.size(), 0);
}

TEST(ListTest, IteratorsTest)
{
    List<int> list_init {0,1,2,3,4,5,6,7,8,9};

    int value = 0;
    for(auto it = list_init.begin(); it != list_init.end(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }

    value = 0;
    for (auto it = list_init.cbegin(); it != list_init.cend(); ++it, value++) {
        ASSERT_EQ(*it, value);
    }

    value = 9;
    for (auto it = list_init.rbegin(); it != list_init.rend(); ++it, value--) {
        ASSERT_EQ(*it, value);
    }
}

TEST(ListTest, FindTest)
{
    List<int> list {0,11,22,33,44,55,66,77,88,99};
    auto item = list.find(22);
    auto end = list.find(-1);

    ASSERT_EQ(end, list.end());
    //ASSERT_EQ(item, list.begin() + 2);
}

TEST(ListTest, AssignTest)
{
    std::initializer_list<int> init_list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    List<int> list_init (init_list);

    List<int> list_copy;
    list_copy = list_init;
    ASSERT_EQ(list_copy, list_init);

    List<int> list_move;
    list_move = std::move(list_init);
    ASSERT_EQ(list_move, list_copy);
    ASSERT_EQ(list_init.size(), 0);

    List<int> non_equal {10,11,12,13,14,15};
    ASSERT_NE(non_equal, list_move);
}

TEST(ListTest, AccessTest)
{
    List<int> list { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    try {
        const int var = list[66];
        (void)(var);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::list<T>::operator[]: index is out of range"));
    }

    list[5] = 50;
    int var = list[5];
    ASSERT_EQ(var, 50);
}

TEST(ListTest, InsertTest)
{
    /*List<int> list {0, 1, 2, 3, 4, 5, 6, 7};
    int value { -11 };

    list.insert(value, 0);
    list.insert(100, list.begin());
    list.insert(9000, list.size());
    list.insert(1234, list.end());
    list.insert(789, 5);

    ASSERT_EQ(list, List<int>({100, -11, 0, 1, 2, 789, 3, 4, 5, 6, 7, 9000, 1234}));
    ASSERT_EQ(list.size(), 13);

    try {
        list.insert(42, 666);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::list<T>::insert: index is out of range"));
    }
    try {
        list.insert(42, list.begin() - 666);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::list<T>::insert: iterator is invalid"));
    }*/

}

TEST(ListTest, RemoveTest)
{
    List<int> list {0, 1, 2, 3, 4, 5, 6, 7};

    /*list.remove(3);
    list.remove(list.begin() + 2);
    list.remove(list.begin());
    list.remove(--list.end());

    ASSERT_EQ(list, List<int>({1,4,5,6}));
    ASSERT_EQ(list.size(), 4);

    list.clear();
    ASSERT_EQ(list.size(), 0);

    try {
        list.remove(66);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::list<T>::remove: index is out of range"));
    }

    try {
        list.remove(list.begin() - 99);
    } catch (std::out_of_range& exception) {
        ASSERT_EQ(exception.what(), std::string("CppADS::list<T>::remove: iterator is invalid"));
    }*/
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
