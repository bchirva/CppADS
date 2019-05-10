#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Container.hpp"

#include <memory>

namespace CppADS
{
    template<class T>
    /// @brief Queue (FIFO) class
    class Queue : public IContainer
    {
    public:
        Queue() = default;                              ///< Defualt constructor
        Queue(const Queue<T>& copy);                    ///< Copy contructor
        Queue(Queue<T>&& move);                         ///< Move constructor
        Queue(std::initializer_list<T> init_list);      ///< Constructor form initializer list

        Queue& operator=(const Queue<T>& copy);         ///< Copy assignment operator
        Queue& operator=(Queue<T>&& move);              ///< Move assignment operator

        ~Queue() = default;                             ///< Destructor

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Add value to tail of queue
        /// @param value added value
        void enqueue(const T& value);

        /// @brief Overloaded method
        void enqueue(T&& value);

        /// @brief Remove front element
        void dequeue();

        /// @brief Get first inserted value 
        /// @return value on fron of the queue
        T& front();

        /// @brief Overloaded method
        const T& front() const;

    private:
        struct Node
        {
            T Value;
            std::shared_ptr<Node> Next { nullptr };
            Node(T _value, std::shared_ptr<Node>&& _next = nullptr)
                : Value(_value), Next(std::move(_next)) {}
        };

        std::shared_ptr<Node> m_tail { nullptr };   ///< Back (last inserted) item
        std::shared_ptr<Node> m_head { nullptr };   ///< Front (first inserted) item
        size_t m_size { 0 };
    };
}

template<typename T>
CppADS::Queue<T>::Queue(const Queue<T>& copy)
{
    m_size = copy.m_size;

    std::shared_ptr<Node>* self_node = &m_head;
    const std::shared_ptr<Node>* self_back_node = nullptr;
    const std::shared_ptr<Node>* copy_node = &(copy.m_head);

    while ((*copy_node) != nullptr)
    {
        *self_node = std::make_shared<Node>(copy_node->get()->Value);

        self_back_node = self_node;
        self_node = &(self_node->get()->Next);
        copy_node = &(copy_node->get()->Next);
    }
    m_tail = *self_back_node;
}

template<typename T>
CppADS::Queue<T>::Queue(Queue<T>&& move)
{
    m_size = std::move(move.m_size);
    m_tail = std::move(move.m_tail);
    m_head = std::move(move.m_head);
    move.m_size = 0;
}

template<typename T>
CppADS::Queue<T>::Queue(std::initializer_list<T> init_list)
{
    for(auto it = std::rbegin(init_list); it != std::rend(init_list); it++)
    {
        enqueue(*it);
    }
}

template<typename T>
CppADS::Queue<T>& CppADS::Queue<T>::operator=(const Queue<T>& copy)
{
    m_size = copy.m_size;

    std::shared_ptr<Node>* self_node = &m_head;
    const std::shared_ptr<Node>* self_back_node = nullptr;
    const std::shared_ptr<Node>* copy_node = &(copy.m_head);

    while ((*copy_node) != nullptr)
    {
        *self_node = std::make_shared<Node>(copy_node->get()->Value);

        self_back_node = self_node;
        self_node = &(self_node->get()->Next);
        copy_node = &(copy_node->get()->Next);
    }
    m_tail = *self_back_node;
    return *this;
}

template<typename T>
CppADS::Queue<T>& CppADS::Queue<T>::operator=(Queue<T>&& move)
{
    m_size = std::move(move.m_size);
    m_tail = std::move(move.m_tail);
    m_head = std::move(move.m_head);
    move.m_size = 0;
    
    return *this;
}

template<typename T>
size_t CppADS::Queue<T>::size() const
{
    return m_size;
}

template<typename T>
void CppADS::Queue<T>::clear()
{
    m_tail.reset();
    m_head.reset();
    m_size = 0;
}

template<typename T>
void CppADS::Queue<T>::enqueue(const T& value)
{
    if (m_tail != nullptr)
    {
        m_tail->Next = std::make_shared<Node>(value, nullptr);
        m_tail = m_tail->Next;
    }
    else
    {
        m_tail = m_head = std::make_shared<Node>(value, nullptr);
    }

    m_size++;
}

template<typename T>
void CppADS::Queue<T>::enqueue(T&& value)
{
    if (m_tail != nullptr)
    {
        m_tail->Next = std::make_shared<Node>(std::move(value), nullptr);
        m_tail = m_tail->Next;
    }
    else
    {
        m_tail = m_head = std::make_shared<Node>(std::move(value), nullptr);
    }

    m_size++;
}

template<typename T>
void CppADS::Queue<T>::dequeue()
{
    m_head = std::move(m_head->Next);
    m_size--;

    if(m_tail.unique())
        m_tail.reset();
}

template<typename T>
T& CppADS::Queue<T>::front()
{
    return m_head->Value;
}

template<typename T>
const T& CppADS::Queue<T>::front() const
{
    return m_head->Value;
}

#endif
