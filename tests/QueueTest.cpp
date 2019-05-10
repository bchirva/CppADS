#include <gtest/gtest.h>

#include <Queue.hpp>

using CppADS::Queue;

TEST(QueueTest, ConstructQueueTest)
{
    Queue<int> queue_empty;
    ASSERT_EQ(queue_empty.size(), 0);

    Queue<int> queue_init {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(queue_init.size(), 10);

    Queue<int> queue_copy(queue_init);
    ASSERT_EQ(queue_copy.size(), queue_init.size());

    Queue<int> queue_move(std::move(queue_init));
    ASSERT_EQ(queue_move.size(), queue_copy.size());
    ASSERT_EQ(queue_init.size(), 0);
}

TEST(QueueTest, AssignQueueTest)
{
    Queue<int> queue_init { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto init_size = queue_init.size();

    Queue<int> queue_copy;
    queue_copy = queue_init;
    ASSERT_EQ(queue_copy.size(), init_size);
    
    Queue<int> queue_move;
    queue_move = std::move(queue_init);
    ASSERT_EQ(queue_move.size(), init_size);
    ASSERT_EQ(queue_init.size(), 0);
}

TEST(QueueTest, ModifyQueueTest)
{
    Queue<int> queue;
    for (int i = 100; i > 0; i--)
        queue.enqueue(i);

    ASSERT_EQ(queue.size(), 100);
    ASSERT_EQ(queue.front(), 100);

    while(queue.size() > 50)
        queue.dequeue();
    
    ASSERT_EQ(queue.size(), 50);
    ASSERT_EQ(queue.front(), 50);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
