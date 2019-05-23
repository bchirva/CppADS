#pragma once

#include "Container.hpp"

#include <memory>
#include <iterator>

namespace CppADS
{
    template<class T>
    /// @brief Dynamic array class
    class Array : public IContainer
    {
    public:
        class Iterator;
        class ConstIterator;
        
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        Array() = default;                          ///< Default constructor
        ~Array() = default;                         ///< Destructor
        Array(const Array<T>& copy);                ///< Copy contructor
        Array(Array<T>&& move);                     ///< Move contructor
        Array<T>& operator=(const Array<T>& copy);  ///< Copy assignment operator
        Array<T>& operator=(Array<T>&& move);       ///< Move assignment operator
        Array(std::initializer_list<T> init_list);  ///< Contructor from initializer list
        
        /// @brief Remove all data from container
        void clear() override;
        
        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;
        
        /// @brief Insert value container
        /// @param value inserted value
        /// @param index position to insert
        void insert(const T& value, size_t index);
        
        /// @brief Overloaded method 
        void insert(T&& value, size_t index);
        
        /// @brief Remove values from container
        /// @param index position of first item to delete
        /// @param count count of deleted elements
        void remove(size_t index, uint32_t count = 1);
        
        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        T& operator[](size_t index);
        
        /// @brief Const overloaded method
        const T& operator[](size_t index) const;

        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator crbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        const_reverse_iterator crend() const;
        
    private:
        std::unique_ptr<T[]> m_data { nullptr };      ///< Pointer to the data head on heap
        size_t m_size { 0 };                          ///< Array size        
    };

    template<typename T>
    class Array<T>::Iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        reference operator*();
        reference operator->();
        reference operator[](int AIndex);

        Iterator& operator++();
        Iterator& operator--();
        Iterator& operator+(int AOffset);
        Iterator& operator-(int AOffset);
        
        bool operator==(const Iterator& rhs);
        bool operator!=(const Iterator& rhs);
        bool operator>(const Iterator& rhs);
        bool operator<(const Iterator& rhs);
        bool operator>=(const Iterator& rhs);
        bool operator<=(const Iterator& rhs);

    private:
        size_t m_Index { 0 };
    };
}

template<typename T> 
CppADS::Array<T>::Array(const Array<T>& copy)
{
    m_size = copy.m_size;
    m_data.reset(new T[m_size]);
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = copy.m_data[i];
    }
}

template<typename T> 
CppADS::Array<T>::Array(Array<T>&& move)
{
    m_size = std::move(move.m_size);
    m_data = std::move(move.m_data);
    move.m_size = 0;
}

template<typename T> 
CppADS::Array<T>::Array(std::initializer_list<T> init_list)
{
    m_size = init_list.size();
    m_data.reset(new T[m_size]);
    int i = 0;
    for(auto it = init_list.begin(); it != init_list.end(); it++)
    {
        m_data[i] = *it;
        i++;
    }
}

template<typename T> 
CppADS::Array<T>& CppADS::Array<T>::operator=(const Array<T>& copy)
{
    m_size = copy.m_size;
    m_data.reset(new T[m_size]);
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = copy.m_data[i];
    }
    return *this;
}

template<typename T> 
CppADS::Array<T>& CppADS::Array<T>::operator=(Array<T>&& move)
{
    m_size = std::move(move.m_size);
    m_data = std::move(move.m_data);
    move.m_size = 0;
    return *this;
}


template<typename T> 
void CppADS::Array<T>::clear()
{
    m_data.reset(nullptr);
    m_size = 0;
}

template<typename T> 
size_t CppADS::Array<T>::size() const
{
    return m_size;
}

template<typename T> 
void CppADS::Array<T>::insert(const T& value, size_t index)
{
    if (index > m_size)
        throw std::out_of_range("CppADS::Array<T>::insert: index out of range");

    m_size++;
    std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_size);
    for (int i = 0; i < index; i++)
        tmp[i] = m_data[i];

    tmp[index] = value;

    for (int i = index + 1; i < m_size; i++)
        tmp[i] = m_data[i - 1];
    
    m_data = std::move(tmp);
}

template<typename T> 
void CppADS::Array<T>::insert(T&& value, size_t index)
{
    if (index > m_size)
        throw std::out_of_range("CppADS::Array<T>::insert: index is out of range");

    m_size++;
    std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_size);
    for (int i = 0; i < index; i++)
        tmp[i] = m_data[i];

    tmp[index] = std::move(value);

    for (int i = index + 1; i < m_size; i++)
        tmp[i] = m_data[i - 1];
    
    m_data = std::move(tmp);
}

template<typename T> 
void CppADS::Array<T>::remove(size_t index, uint32_t count)
{
    if (index > m_size)
        throw std::out_of_range("CppADS::Array<T>::remove: index is out of range");
    if (count > (m_size - index))
        throw std::out_of_range("CppADS::Array<T>::remove: count is out of range");

    m_size -= count;
    std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_size);

    for (int i = 0; i < index; i++)
        tmp[i] = m_data[i];
    for (int i = index; i < m_size; i++)
        tmp[i] = m_data[i + count];

    m_data = std::move(tmp);
}

template<typename T>
T& CppADS::Array<T>::operator[](size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::Array<T>::operator[]: index is out of range");
    return m_data[index];
}

template<typename T>
const T& CppADS::Array<T>::operator[](size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::Array<T>::operator[]: index is out of range");
    return m_data[index];
}

