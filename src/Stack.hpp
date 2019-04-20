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

        struct Cell
        {
            std::shared_ptr<Cell> Next { nullptr };
            T Value;
        };

        std::unique_ptr<Cell> m_head { nullptr };   ///< Pointer to the top of the stack
        size_t m_size { 0 };                        ///< Stack size
    };
}

template<class T>
CppADS::Stack<T>::Stack(const Stack<T>& copy)
{

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

}

template<class T>
void CppADS::Stack<T>::clear()
{

}

template<class T>
size_t CppADS::Stack<T>::size() const
{

}

template<class T>
void CppADS::Stack<T>::push(const T& value)
{

}

template<class T>
void CppADS::Stack<T>::push(T&& value)
{

}

template<class T>
T CppADS::Stack<T>::pop()
{

}


