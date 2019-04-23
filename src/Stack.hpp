#pragma once

#include "Container.hpp"

#include <memory>

namespace CppADS
{
    template<class T>
    /// @brief Stack (LIFO) class
    class Stack : public IContainer
    {
    public:
        Stack() = default;                          ///< Default constructor
        ~Stack() = default;                         ///< Destructor
        Stack(const Stack<T>& copy);                ///< Copy contructor
        Stack(Stack<T>&& move);                     ///< Move contructor
        Stack<T>& operator=(const Stack<T>& copy);  ///< Copy assignment operator
        Stack<T>& operator=(Stack<T>&& move);       ///< Move assignment operator
        Stack(std::initializer_list<T> init_list);  ///< Contructor from initializer list

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Push value on top of the stack
        /// @param value inserted value
        void push(const T& value);

        /// @brief Overloaded method
        void push(T&& value);

        /// @brief Remove and return last inserted value
        /// @return value on top of the stack
        T pop();

    private:

        struct Node
        {
            T Value;
            std::unique_ptr<Node> Next { nullptr };
            Node(T _value, std::unique_ptr<Node> _next) : Value(_value), Next(std::move(_next)) {}
        };

        std::unique_ptr<Node> m_head { nullptr };   ///< Pointer to the top of the stack
        size_t m_size { 0 };                        ///< Stack size
    };
}

template<class T>
CppADS::Stack<T>::Stack(const Stack<T>& copy)
{
    m_size = copy.m_size; 

}

template<class T>
CppADS::Stack<T>::Stack(Stack<T>&& move)
{

}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(const Stack<T>& copy)
{

}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(Stack<T>&& move)
{

}

template<class T>
CppADS::Stack<T>::Stack(std::initializer_list<T> init_list)
{
    m_size = init_list.size();

    for (auto it = init_list.begin(); it != init_list.end(); it++)
    {
        push(*it);
    }
}

template<class T>
void CppADS::Stack<T>::clear()
{
    m_head.reset(nullptr);
    m_size = 0;
}

template<class T>
size_t CppADS::Stack<T>::size() const
{
    return m_size;
}

template<class T>
void CppADS::Stack<T>::push(const T& value)
{
    std::unique_ptr<Node> new_top = std::make_unique<Node>(value, std::move(m_head));
    m_head = std::move(new_top);
}

template<class T>
void CppADS::Stack<T>::push(T&& value)
{
    std::unique_ptr<Node> new_top = std::make_unique<Node>(std::move(value), std::move(m_head));
    m_head = std::move(new_top);
}

template<class T>
T CppADS::Stack<T>::pop()
{
    T value = std::move(m_head.Value);
    m_head = std::move(m_head->Next);
    return value;
}


