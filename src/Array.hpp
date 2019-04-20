#pragma once

#include "Container.hpp"

#include <memory>

namespace CppADS
{
    template<class T>
    /// @brief Dynamic array class
    class Array : public IContainer
    {
    public:
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
        
    private:
        std::unique_ptr<T[]> m_data { nullptr };      ///< Pointer to the data head on heap
        size_t m_size { 0 };                          ///< Array size        
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
    m_size++;
    std::unique_ptr<T[]> tmp = std::make_unique<T[]>(new T[m_size]);
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
    m_size++;
    std::unique_ptr<T[]> tmp = std::make_unique<T[]>(new T[m_size]);
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
    m_size =- count;
    std::unique_ptr<T[]> tmp = std::make_unique<T[]>(new T[m_size]);

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
        throw std::out_of_range("T& CppADS::Array<T>::operator[]: index out of range");
    return m_data[index];
}

template<typename T>
const T& CppADS::Array<T>::operator[](size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range("const T& CppADS::Array::operator[] const: index out of range");
    return m_data[index];
}

