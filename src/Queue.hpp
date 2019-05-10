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
            std::shared_ptr<T> Next { nullptr };
            Node(T _value, std::shared_ptr<Node>&& _next = nullptr)
                : Value(_value), Next(std::move(_next)) {}
        };

        std::shared_ptr<Node> m_head { nullptr };
        std::shared_ptr<Node> m_tail { nullptr };
        size_t m_size { 0 };
    };
}

template<typename T>
CppADS::Queue<T>::Queue(const Queue<T>& copy)
{

}

template<typename T>
CppADS::Queue<T>::Queue(Queue<T>&& move)
{

}

template<typename T>
CppADS::Queue<T>::Queue(std::initializer_list<T> init_list)
{

}

template<typename T>
CppADS::Queue<T>& CppADS::Queue<T>::operator=(const Queue<T>& copy)
{

}

template<typename T>
CppADS::Queue<T>& CppADS::Queue<T>::operator=(Queue<T>&& move)
{

}

template<typename T>
size_t CppADS::Queue<T>::size() const
{
    return m_size;
}

template<typename T>
void CppADS::Queue<T>::clear()
{
    m_head.reset(nullptr);
    m_tail.reset(nullptr);
    m_size = 0;
}

template<typename T>
void CppADS::Queue<T>::enqueue(const T& value)
{
    m_head->Next = std::make_shared<Node>(value, nullptr);
    m_head = m_head.Next;

    m_size++;

    if (m_tail == nullptr)
        m_tail = m_head;
}

template<typename T>
void CppADS::Queue<T>::enqueue(T&& value)
{
    m_head->Next = std::make_shared<Node>(std::move(value), nullptr);
    m_head = m_head.Next;

    m_size++;

    if (m_tail == nullptr)
        m_tail = m_head;
}

template<typename T>
void CppADS::Queue<T>::dequeue()
{
    m_tail = std::move(m_tail->Next);
    m_size--;

    if(m_tail == nullptr)
        m_head.reset(nullptr);
}

template<typename T>
T& CppADS::Queue<T>::front()
{
    return m_tail->Value;
}

template<typename T>
const T& CppADS::Queue<T>::front() const
{
    return m_tail->Value;
}

#endif
