#ifndef STACK_H
#define STACK_H

#include "Container.hpp"
#include "Array.hpp"

#include <memory>

namespace CppADS
{
    template<class T>
    /// @brief Stack (LIFO) class
    class Stack : private Array<T>
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        class iterator;
        class const_iterator;

        Stack() = default;                          ///< Default constructor
        Stack(const Stack<T>& copy);                ///< Copy contructor
        Stack(Stack<T>&& move);                     ///< Move contructor
        Stack(std::initializer_list<T> init_list);  ///< Contructor from initializer list

        Stack<T>& operator=(const Stack<T>& copy);  ///< Copy assignment operator
        Stack<T>& operator=(Stack<T>&& move);       ///< Move assignment operator

        ~Stack() = default;                         ///< Destructor

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Push value on top of the stack
        /// @param value added value
        void push(const T& value);

        /// @brief Overloaded method
        void push(T&& value);

        /// @brief Get last inserted value
        /// @return value on top of the stack
        T& top();

        /// @brief Overloaded method
        const T& top() const;

        /// @brief Remove top item
        void pop();

        iterator begin() {
            return iterator(Array<T>::rbegin());
        }
        const_iterator begin() const {
            return const_iterator(Array<T>::rbegin());
        }
        const_iterator cbegin() const {
            return const_iterator(Array<T>::crbegin());
        }
        iterator end() {
            return iterator(Array<T>::rend());
        }
        const_iterator end() const {
            return const_iterator(Array<T>::rend());
        }
        const_iterator cend() const {
            return const_iterator(Array<T>::crend());
        }
    };

    template<typename T>
    class Stack<T>::iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    private:
        typename Array<T>::reverse_iterator it { nullptr };

    public:
        iterator(typename Array<T>::reverse_iterator src_it = nullptr) : it(src_it) {}
        ~iterator() = default;

        Stack<T>::reference operator*() {
            return *it;
        }
        Stack<T>::pointer operator->() {
            return it.operator->();
        }

        iterator& operator++() {
            it++;
            return *this;
        }
        iterator& operator--() {
            it--;;
            return *this;
        }
        iterator& operator++(int) {
            it++;
            return *this;
        }
        iterator& operator--(int) {
            it--;;
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return it == rhs.it;
        }
        bool operator!=(const iterator& rhs) const {
            return it != rhs.it;
        }
    };

    template<typename T>
    class Stack<T>::const_iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    private:
        typename Array<T>::reverse_iterator it;

    public:
        const_iterator(typename Array<T>::reverse_iterator src_it = nullptr) : it(src_it) {}
        ~const_iterator() = default;

        Stack<T>::const_reference operator*() {
            return *it;
        }
        Stack<T>::const_pointer operator->() {
            return it.operator->();
        }

        const_iterator& operator++() {
            it++;
            return *this;
        }
        const_iterator& operator--() {
            it--;;
            return *this;
        }
        const_iterator& operator++(int) {
            it++;
            return *this;
        }
        const_iterator& operator--(int) {
            it--;;
            return *this;
        }

        bool operator==(const const_iterator& rhs) const {
            return it == rhs.it;
        }
        bool operator!=(const const_iterator& rhs) const {
            return it != rhs.it;
        }
    };
}

template<class T>
CppADS::Stack<T>::Stack(const Stack<T>& copy)
    : Array<T>(copy)
{}

template<class T>
CppADS::Stack<T>::Stack(Stack<T>&& move)
    : Array<T>(move)
{}

template<class T>
CppADS::Stack<T>::Stack(std::initializer_list<T> init_list)
    : Array<T>(init_list)
{}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(const Stack<T>& copy)
{
    Array<T>::operator=(copy);
    return *this;
}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(Stack<T>&& move)
{
    Array<T>::operator=(move);
    return *this;
}

template<class T>
void CppADS::Stack<T>::clear()
{
    Array<T>::clear();
}

template<class T>
size_t CppADS::Stack<T>::size() const
{
    return Array<T>::size();
}

template<class T>
void CppADS::Stack<T>::push(const T& value)
{
    Array<T>::insert(value, Array<T>::end());
}

template<class T>
void CppADS::Stack<T>::push(T&& value)
{
    Array<T>::insert(value, Array<T>::end());
}

template<class T>
T& CppADS::Stack<T>::top()
{
    return Array<T>::operator[](Array<T>::size() - 1);
}

template<class T>
const T& CppADS::Stack<T>::top() const
{
    return Array<T>::operator[](Array<T>::size() - 1);
}

template<class T>
void CppADS::Stack<T>::pop()
{
    Array<T>::remove(Array<T>::end());
}
#endif //STACK_H
