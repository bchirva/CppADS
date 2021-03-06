#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "forward_list.hpp"

namespace CppADS
{
    /// @brief FIFO data structure class
    /// @tparam T value type stored in the container
    template<class T>
    class Queue : private ForwardList<T>
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        Queue() = default;                              ///< Defualt constructor
        Queue(const Queue<T>& copy);                    ///< Copy contructor
        Queue(Queue<T>&& move);                         ///< Move constructor
        Queue(std::initializer_list<T> init_list);      ///< Constructor form initializer list

        Queue& operator=(const Queue<T>& copy);         ///< Copy assignment operator
        Queue& operator=(Queue<T>&& move);              ///< Move assignment operator

        ~Queue() = default;                             ///< Destructor

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

        /// @brief Add value to tail of queue
        /// @param value added value
        void enqueue(const T& value);

        /// @brief Add value to tail of queue
        /// @param value added value
        void enqueue(T&& value);

        /// @brief Remove front element
        void dequeue();

        ///@}
        /// @name Accesors
        /// @{

        /// @brief Get first inserted value
        /// @return reference to the first item of the queue
        reference front();
        /// @brief Get first inserted value
        /// @return const reference to the first item of the queue
        const_reference front() const;

        /// @}
    };
}

template<typename T>
CppADS::Queue<T>::Queue(const Queue<T>& copy) : ForwardList<T>(copy) {}

template<typename T>
CppADS::Queue<T>::Queue(Queue<T>&& move) : ForwardList<T>(std::move(move)) {}

template<typename T>
CppADS::Queue<T>::Queue(std::initializer_list<T> init_list) : ForwardList<T>(init_list) {}

template<typename T>
CppADS::Queue<T>& CppADS::Queue<T>::operator=(const Queue<T>& copy)
{
    ForwardList<T>::operator=(copy);
    return *this;
}

template<typename T>
CppADS::Queue<T>& CppADS::Queue<T>::operator=(Queue<T>&& move)
{
    ForwardList<T>::operator=(std::move(move));
    return *this;
}

template<typename T>
size_t CppADS::Queue<T>::size() const
{
    return ForwardList<T>::size();
}

template<typename T>
void CppADS::Queue<T>::clear()
{
    ForwardList<T>::clear();
}

template<typename T>
void CppADS::Queue<T>::enqueue(const T& value)
{
    ForwardList<T>::push_back(value);
}

template<typename T>
void CppADS::Queue<T>::enqueue(T&& value)
{
    ForwardList<T>::push_back(std::move(value));
}

template<typename T>
void CppADS::Queue<T>::dequeue()
{
    ForwardList<T>::pop_front();
}

template<typename T>
typename CppADS::Queue<T>::reference CppADS::Queue<T>::front()
{
    return ForwardList<T>::front();
}

template<typename T>
typename CppADS::Queue<T>::const_reference CppADS::Queue<T>::front() const
{
    return ForwardList<T>::front();
}

#endif //QUEUE_HPP
