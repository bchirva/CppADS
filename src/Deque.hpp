#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "List.hpp"

namespace CppADS
{
    template<typename T>
    /// @brief Double-endian queue class
    class Deque : private List<T>
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        Deque() = default;                          ///< Default constructor
        Deque(const Deque<T>& copy);                ///< Copy constructor
        Deque(Deque<T>&& move);                     ///< Move constructor
        Deque(std::initializer_list<T> init_list);  ///< Contructor from initializer list

        Deque<T>& operator=(const Deque<T>& copy);  ///< Copy assignment operator
        Deque<T>& operator=(Deque<T>&& move);       ///< Move assignment operator

        ~Deque() = default;                         ///< Destructor

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

        /// @brief Insert element to the end
        /// @param value inserted item
        void push_back(const T& value);

        /// @brief Overloaded method
        void push_back(T&& value);

        /// @brief Insert element to the beginning
        /// @param value
        void push_front(const T& value);

        /// @brief Overloaded method
        void push_front(T&& value);

        /// @brief Remove last element
        void pop_back();

        /// @brief Remove first element
        void pop_front();

        ///@}
        /// @name Accesors
        /// @{

        /// @brief Access to the first element
        /// @return Reference to the first element
        reference front();

        /// @brief Access to the first element
        /// @return Reference to the first element
        const_reference front() const;

        /// @brief Access to the last element
        /// @return Reference to the last element
        reference back();

        /// @brief Access to the last element
        /// @return Reference to the last element
        const_reference back() const;

        ///@}
    };
}

template<typename T>
CppADS::Deque<T>::Deque(const Deque<T>& copy) : List<T>(copy) {}

template<typename T>
CppADS::Deque<T>::Deque(Deque<T>&& move) : List<T>(std::move(move)) {}

template<typename T>
CppADS::Deque<T>::Deque(std::initializer_list<T> init_list) : List<T>(init_list) {}

template<typename T>
CppADS::Deque<T>& CppADS::Deque<T>::operator=(const Deque<T>& copy)
{
    List<T>::operator=(copy);
    return *this;
}

template<typename T>
CppADS::Deque<T>& CppADS::Deque<T>::operator=(Deque<T>&& move)
{
    List<T>::operator=(std::move(move));
    return *this;
}

template<typename T>
void CppADS::Deque<T>::push_back(const T& value)
{
    List<T>::push_back(value);
}

template<typename T>
void CppADS::Deque<T>::push_back(T&& value)
{
    List<T>::push_back(std::move(value));
}

template<typename T>
void CppADS::Deque<T>::push_front(const T& value)
{

    List<T>::push_front(value);
}

template<typename T>
void CppADS::Deque<T>::push_front(T&& value)
{
    List<T>::push_front(std::move(value));
}

template<typename T>
void CppADS::Deque<T>::pop_back()
{
    List<T>::pop_back();
}

template<typename T>
void CppADS::Deque<T>::pop_front()
{
    List<T>::pop_front();
}

template<typename T>
typename CppADS::Deque<T>::reference CppADS::Deque<T>::front()
{
    return List<T>::front();
}

template<typename T>
typename CppADS::Deque<T>::const_reference CppADS::Deque<T>::front() const
{
    return List<T>::front();
}

template<typename T>
typename CppADS::Deque<T>::reference CppADS::Deque<T>::back()
{
    return List<T>::back();
}

template<typename T>
typename CppADS::Deque<T>::const_reference CppADS::Deque<T>::back() const
{
    return List<T>::back();
}

template<typename T>
size_t CppADS::Deque<T>::size() const
{
    return List<T>::size();
}

template<typename T>
void CppADS::Deque<T>::clear()
{
    List<T>::clear();
}

#endif //DEQUE_HPP
