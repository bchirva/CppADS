#ifndef STACK_H
#define STACK_H

#include "ForwardList.hpp"

namespace CppADS
{
    /// @brief LIFO data structure class
    /// @tparam T value type stored in the container
    template<class T>
    class Stack : private ForwardList<T>
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        Stack() = default;                          ///< Default constructor
        Stack(const Stack<T>& copy);                ///< Copy contructor
        Stack(Stack<T>&& move);                     ///< Move contructor
        Stack(std::initializer_list<T> init_list);  ///< Contructor from initializer list

        Stack<T>& operator=(const Stack<T>& copy);  ///< Copy assignment operator
        Stack<T>& operator=(Stack<T>&& move);       ///< Move assignment operator

        ~Stack() = default;                         ///< Destructor

        /// @name Capacity
        /// @{

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @}
        /// @name Modifiers
        /// @{

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Push value on top of the stack
        /// @param value added value
        void push(const T& value);

        /// @brief Push value on top of the stack
        /// @param value added value
        void push(T&& value);

        /// @brief Remove top item
        void pop();

        ///@}
        /// @name Accesors
        /// @{

        /// @brief Get last inserted value
        /// @return reference to the item on top of the stack
        reference top();

        /// @brief Get last inserted value
        /// @return const reference to the item on top of the stack
        const_reference top() const;

        /// @}
    };
}

template<class T>
CppADS::Stack<T>::Stack(const Stack<T>& copy) : ForwardList<T>(copy) {}

template<class T>
CppADS::Stack<T>::Stack(Stack<T>&& move) : ForwardList<T>(std::move(move)) {}

template<class T>
CppADS::Stack<T>::Stack(std::initializer_list<T> init_list) : ForwardList<T>(init_list) {}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(const Stack<T>& copy)
{
    ForwardList<T>::operator=(copy);
    return *this;
}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(Stack<T>&& move)
{
    ForwardList<T>::operator=(std::move(move));
    return *this;
}

template<class T>
void CppADS::Stack<T>::clear()
{
    ForwardList<T>::clear();
}

template<class T>
size_t CppADS::Stack<T>::size() const
{
    return ForwardList<T>::size();
}

template<class T>
void CppADS::Stack<T>::push(const T& value)
{
    ForwardList<T>::push_front(value);
}

template<class T>
void CppADS::Stack<T>::push(T&& value)
{
    ForwardList<T>::push_front(std::move(value));
}

template<class T>
typename CppADS::Stack<T>::reference CppADS::Stack<T>::top()
{
    return ForwardList<T>::front();
}

template<class T>
typename CppADS::Stack<T>::const_reference CppADS::Stack<T>::top() const
{
    return ForwardList<T>::front();
}

template<class T>
void CppADS::Stack<T>::pop()
{
    ForwardList<T>::pop_front();
}
#endif //STACK_H
