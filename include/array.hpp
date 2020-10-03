#ifndef ARRAY_H
#define ARRAY_H

#include "container.hpp"

#include <cmath>
#include <functional>
#include <iterator>
#include <memory>

namespace CppADS
{
/// @brief Dynamic array class
/// @tparam T value type stored in the container
template<class T>
class Array : public IContainer
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    class iterator;
    class const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Array() = default;                         ///< Default constructor
    Array(const Array<T>& copy);               ///< Copy contructor
    Array(Array<T>&& move);                    ///< Move contructor
    Array(std::initializer_list<T> init_list); ///< Contructor from initializer list

    Array<T>& operator=(const Array<T>& copy); ///< Copy assignment operator
    Array<T>& operator=(Array<T>&& move);      ///< Move assignment operator

    ~Array() = default; ///< Destructor

    /// @name Capacity
    /// @{

    /// @brief Get size of container
    /// @return element's count
    size_t size() const override;

    /// @brief Get reserved size for container's data
    /// @return Current array's capacity
    size_t capacity() const;

    /// @}
    /// @name Modifiers
    /// @{

    /// @brief Remove all data from container
    void clear() override;

    /// @brief Reserve space for specific count of items
    /// @param count reserved space
    void reserve(size_t count);

    /// @brief Insert value to container
    /// @param value inserted value
    /// @param index position to insert
    void insert(const T& value, size_t index);

    /// @brief Insert value to container
    /// @param value inserted value
    /// @param index position to insert
    void insert(T&& value, size_t index);

    /// @brief Insert value to container
    /// @param value inserted value
    /// @param position position to insert
    void insert(const T& value, iterator position);

    /// @brief Insert value to container
    /// @param value inserted value
    /// @param position position to insert
    void insert(T&& value, iterator position);

    /// @brief Push value to the back of container
    /// @param value inserted value
    void push_back(const T& value);

    /// @brief Push value to the back of container
    /// @param value inserted value
    void push_back(T&& value);

    /// @brief Add value to the head of container
    /// @param value - added value
    void push_front(const T& value);

    /// @brief Add value to the head of container
    /// @param value - added value
    void push_front(T&& value);

    /// @brief Remove values from container
    /// @param index position of item to delete
    void remove(size_t index);

    /// @brief Remove values from container
    /// @param position position of item to delete
    void remove(iterator position);

    /// @brief Remove last item from container
    void pop_back();

    /// @brief Remove first value of the container
    void pop_front();

    /// @}
    /// @name Accesors
    /// @{

    /// @brief Access to item
    /// @param index item position
    /// @return reference to value
    reference operator[](size_t index);

    /// @brief Access to item
    /// @param index item position
    /// @return reference to value
    const_reference operator[](size_t index) const;

    /// @brief Access to the last item in list
    /// @return reference on first value
    reference back();
    /// @brief Access to the last item in list
    /// @return const reference on first value
    const_reference back() const;
    /// @brief Access to the first item in list
    /// @return reference on first value
    reference front();
    /// @brief Access to the first item in list
    /// @return const reference on first value
    const_reference front() const;

    /// @brief Search for first item equal value
    /// @param value value search for
    /// @return iterator to found item (end if item not found)
    iterator find(const T& value);

    /// @brief Search for first item equal value
    /// @param value value search for
    /// @return iterator to found item (end if item not found)
    const_iterator find(const T& value) const;

    /// @}

    bool operator==(const Array<T>& rhs) const;
    bool operator!=(const Array<T>& rhs) const;

    /// @name Iterators
    /// @{

    /// @return read-write iterator to the first element of the container
    iterator begin();
    /// @return read-only iterator to the first element of the container
    const_iterator begin() const;
    /// @return read-only iterator to the first element of the container
    const_iterator cbegin() const;

    /// @return read-write iterator to the element after the last element of the container
    iterator end();
    /// @return read-only iterator to the element after the last element of the container
    const_iterator end() const;
    /// @return read-only iterator to the element after the last element of the container
    const_iterator cend() const;

    /// @return read-write iterator tto the element after the last element of the container
    reverse_iterator rbegin();
    /// @return read-only iterator to the element after the last element of the container
    const_reverse_iterator rbegin() const;
    /// @return read-only iterator to the element after the last element of the container
    const_reverse_iterator crbegin() const;

    /// @return read-write iterator to the first element of the container
    reverse_iterator rend();
    /// @return read-only iterator to the first element of the container
    const_reverse_iterator rend() const;
    /// @return read-only iterator to the first element of the container
    const_reverse_iterator crend() const;

    /// @}

private:
    std::unique_ptr<T[]> m_data{ nullptr }; ///< Pointer to the data head on heap
    size_t m_size{ 0 };                     ///< Array actual size
    size_t m_capacity{ 0 };                 ///< Reserved size

    /// @private
    /// @brief Allocation size calculation function
    /// @param size for which you need to reserve a space
    /// @return space to resererve
    size_t calc_reserved(size_t size);
};

template<typename T>
/// @brief Read-write iterator for Array container
class Array<T>::iterator : public std::iterator<std::random_access_iterator_tag, T>
{
private:
    T* m_ptr{ nullptr };
    friend class Array;

public:
    iterator(T* src_ptr = nullptr) : m_ptr(src_ptr)
    {
    }
    ~iterator()
    {
        m_ptr = nullptr;
    }

    Array<T>::reference operator*()
    {
        return *m_ptr;
    }
    Array<T>::pointer operator->()
    {
        return m_ptr;
    }
    Array<T>::reference operator[](int AIndex)
    {
        return m_ptr[AIndex];
    }

    iterator& operator++()
    {
        m_ptr++;
        return *this;
    }
    iterator& operator--()
    {
        m_ptr--;
        ;
        return *this;
    }
    iterator& operator++(int)
    {
        m_ptr++;
        return *this;
    }
    iterator& operator--(int)
    {
        m_ptr--;
        ;
        return *this;
    }
    iterator operator+(int AOffset)
    {
        iterator result(m_ptr);
        result.m_ptr += AOffset;
        return result;
    }
    iterator operator-(int AOffset)
    {
        iterator result(m_ptr);
        result.m_ptr -= AOffset;
        return result;
    }

    bool operator==(const iterator& rhs) const
    {
        return m_ptr == rhs.m_ptr;
    }
    bool operator!=(const iterator& rhs) const
    {
        return m_ptr != rhs.m_ptr;
    }
    bool operator>(const iterator& rhs) const
    {
        return m_ptr > rhs.m_ptr;
    }
    bool operator<(const iterator& rhs) const
    {
        return m_ptr < rhs.m_ptr;
    }
    bool operator>=(const iterator& rhs) const
    {
        return m_ptr >= rhs.m_ptr;
    }
    bool operator<=(const iterator& rhs) const
    {
        return m_ptr <= rhs.m_ptr;
    }
};

template<typename T>
/// @brief Read-only iterator for Array container
class Array<T>::const_iterator : public std::iterator<std::random_access_iterator_tag, T>
{
private:
    T* m_ptr{ nullptr };
    friend class Array;

public:
    const_iterator(T* src_ptr = nullptr) : m_ptr(src_ptr)
    {
    }
    ~const_iterator()
    {
        m_ptr = nullptr;
    }

    Array<T>::const_reference operator*()
    {
        return *m_ptr;
    }
    Array<T>::const_pointer operator->()
    {
        return m_ptr;
    }
    Array<T>::const_reference operator[](int AIndex)
    {
        return m_ptr[AIndex];
    }

    const_iterator& operator++()
    {
        m_ptr++;
        return *this;
    }
    const_iterator& operator--()
    {
        m_ptr--;
        ;
        return *this;
    }
    const_iterator& operator++(int)
    {
        m_ptr++;
        return *this;
    }
    const_iterator& operator--(int)
    {
        m_ptr--;
        ;
        return *this;
    }
    const_iterator operator+(int AOffset)
    {
        const_iterator result(m_ptr);
        result.m_ptr += AOffset;
        return result;
    }
    const_iterator operator-(int AOffset)
    {
        const_iterator result(m_ptr);
        result.m_ptr -= AOffset;
        return result;
    }

    bool operator==(const const_iterator& rhs) const
    {
        return m_ptr == rhs.m_ptr;
    }
    bool operator!=(const const_iterator& rhs) const
    {
        return m_ptr != rhs.m_ptr;
    }
    bool operator>(const const_iterator& rhs) const
    {
        return m_ptr > rhs.m_ptr;
    }
    bool operator<(const const_iterator& rhs) const
    {
        return m_ptr < rhs.m_ptr;
    }
    bool operator>=(const const_iterator& rhs) const
    {
        return m_ptr >= rhs.m_ptr;
    }
    bool operator<=(const const_iterator& rhs) const
    {
        return m_ptr <= rhs.m_ptr;
    }
};

} // namespace CppADS

template<typename T>
CppADS::Array<T>::Array(const Array<T>& copy)
{
    reserve(copy.capacity());
    for (auto it = copy.begin(); it != copy.end(); it++)
        push_back(*it);
}

template<typename T>
CppADS::Array<T>::Array(Array<T>&& move)
{
    m_size = std::move(move.m_size);
    m_capacity = std::move(move.m_capacity);
    m_data = std::move(move.m_data);
    move.m_size = 0;
    move.m_capacity = 0;
}

template<typename T>
CppADS::Array<T>::Array(std::initializer_list<T> init_list)
{
    reserve(init_list.size());
    for (auto it = init_list.begin(); it != init_list.end(); it++)
        push_back(*it);
}

template<typename T>
CppADS::Array<T>& CppADS::Array<T>::operator=(const Array<T>& copy)
{
    clear();
    reserve(copy.capacity());
    for (auto it = copy.begin(); it != copy.end(); it++)
        push_back(*it);
    return *this;
}

template<typename T>
CppADS::Array<T>& CppADS::Array<T>::operator=(Array<T>&& move)
{
    m_size = std::move(move.m_size);
    m_capacity = std::move(move.m_capacity);
    m_data = std::move(move.m_data);
    move.m_size = 0;
    move.m_capacity = 0;
    return *this;
}

template<typename T>
void CppADS::Array<T>::clear()
{
    m_data.reset(nullptr);
    m_size = 0;
    m_capacity = 0;
}

template<class T>
void CppADS::Array<T>::reserve(size_t count)
{
    if (count <= capacity())
        return;

    m_capacity = count;
    std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_capacity);
    auto tmp_it = tmp.get();

    for (auto data_it = begin(); data_it != end(); data_it++, tmp_it++)
    {
        *tmp_it = std::move(*data_it);
    }
    m_data = std::move(tmp);
}

template<typename T>
size_t CppADS::Array<T>::size() const
{
    return m_size;
}

template<typename T>
size_t CppADS::Array<T>::capacity() const
{
    return m_capacity;
}

template<typename T>
void CppADS::Array<T>::insert(const T& value, size_t index)
{
    if (index > m_size)
        throw std::out_of_range("CppADS::Array<T>::insert: index is out of range");

    if (m_capacity == m_size)
        reserve(calc_reserved(m_size + 1));

    auto it = end();
    auto insert_it = begin() + index;
    while (it != insert_it)
    {
        *it = std::move(*(it - 1));
        it--;
    }
    *insert_it = value;

    m_size++;
}

template<typename T>
void CppADS::Array<T>::insert(T&& value, size_t index)
{
    if (index > m_size)
        throw std::out_of_range("CppADS::Array<T>::insert: index is out of range");

    if (m_capacity == m_size)
        reserve(calc_reserved(m_size + 1));

    auto it = end();
    auto insert_it = begin() + index;
    while (it != insert_it)
    {
        *it = std::move(*(it - 1));
        it--;
    }
    *insert_it = std::move(value);

    m_size++;
}

template<typename T>
void CppADS::Array<T>::insert(const T& value, iterator position)
{
    if (position > end() || position < begin())
        throw std::out_of_range("CppADS::Array<T>::insert: iterator is invalid");

    if (m_capacity == m_size)
    {
        size_t diff = position.m_ptr - begin().m_ptr;
        reserve(calc_reserved(m_size + 1));
        position = begin() + diff;
    }

    auto it = end();
    while (it != position)
    {
        *it = std::move(*(it - 1));
        it--;
    }
    *position = value;

    m_size++;
}

template<typename T>
void CppADS::Array<T>::insert(T&& value, iterator position)
{
    if (position > end() || position < begin())
        throw std::out_of_range("CppADS::Array<T>::insert: iterator is invalid");

    if (m_capacity == m_size)
    {
        size_t diff = position.m_ptr - begin().m_ptr;
        reserve(calc_reserved(m_size + 1));
        position = begin() + diff;
    }

    auto it = end();
    while (it != position)
    {
        *it = std::move(*(it - 1));
        it--;
    }
    *position = std::move(value);

    m_size++;
}

template<typename T>
void CppADS::Array<T>::push_back(const T& value)
{
    insert(value, end());
}

template<typename T>
void CppADS::Array<T>::push_back(T&& value)
{
    insert(std::move(value), end());
}

template<typename T>
void CppADS::Array<T>::push_front(const T& value)
{
    insert(value, begin());
}

template<typename T>
void CppADS::Array<T>::push_front(T&& value)
{
    insert(std::move(value), begin());
}

template<typename T>
void CppADS::Array<T>::remove(size_t index)
{
    if (index > m_size)
        throw std::out_of_range("CppADS::Array<T>::remove: index is out of range");

    auto it = begin() + index;
    while (it < end())
    {
        *it = std::move(*(it + 1));
        it++;
    }

    m_size--;
}

template<typename T>
void CppADS::Array<T>::remove(iterator position)
{
    if (position > end() || position < begin())
        throw std::out_of_range("CppADS::Array<T>::remove: iterator is invalid");

    while (position < end())
    {
        *position = std::move(*(position + 1));
        position++;
    }
    m_size--;
}

template<typename T>
void CppADS::Array<T>::pop_back()
{
    remove(end()--);
}

template<typename T>
void CppADS::Array<T>::pop_front()
{
    remove(begin());
}

template<class T>
size_t CppADS::Array<T>::calc_reserved(size_t size)
{
    int current_power = std::ceil(std::log2(size));
    return std::pow(2, current_power);
}

template<typename T>
typename CppADS::Array<T>::reference CppADS::Array<T>::operator[](size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::Array<T>::operator[]: index is out of range");
    return m_data[index];
}

template<typename T>
typename CppADS::Array<T>::const_reference CppADS::Array<T>::operator[](size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::Array<T>::operator[]: index is out of range");
    return m_data[index];
}

template<typename T>
typename CppADS::Array<T>::reference CppADS::Array<T>::back()
{
    return *(end()--);
}

template<typename T>
typename CppADS::Array<T>::const_reference CppADS::Array<T>::back() const
{
    return *(cend()--);
}

template<typename T>
typename CppADS::Array<T>::reference CppADS::Array<T>::front()
{
    return *(begin());
}

template<typename T>
typename CppADS::Array<T>::const_reference CppADS::Array<T>::front() const
{
    return *(begin());
}

template<typename T>
typename CppADS::Array<T>::iterator CppADS::Array<T>::find(const T& value)
{
    auto it = begin();
    while (it != end())
    {
        if (*it == value)
            break;
        ++it;
    }
    return it;
}

template<typename T>
typename CppADS::Array<T>::const_iterator CppADS::Array<T>::find(const T& value) const
{
    auto it = cbegin();
    while (it != cend())
    {
        if (*it == value)
            break;
        ++it;
    }
    return it;
}

template<typename T>
bool CppADS::Array<T>::operator==(const Array<T>& rhs) const
{
    if (this->m_size != rhs.m_size)
        return false;

    auto this_it = this->cbegin();
    auto rhs_it = rhs.cbegin();
    while (this_it != this->cend() && rhs_it != rhs.cend())
    {
        if (*this_it != *rhs_it)
            return false;
        ++this_it;
        ++rhs_it;
    }

    return true;
}

template<typename T>
bool CppADS::Array<T>::operator!=(const Array<T>& rhs) const
{
    return !(*this == rhs);
}

template<typename T>
typename CppADS::Array<T>::iterator CppADS::Array<T>::begin()
{
    return iterator(m_data.get());
};

template<typename T>
typename CppADS::Array<T>::const_iterator CppADS::Array<T>::begin() const
{
    return const_iterator(m_data.get());
};

template<typename T>
typename CppADS::Array<T>::const_iterator CppADS::Array<T>::cbegin() const
{
    return const_iterator(m_data.get());
};

template<typename T>
typename CppADS::Array<T>::iterator CppADS::Array<T>::end()
{
    return iterator(m_data.get() + m_size);
};

template<typename T>
typename CppADS::Array<T>::const_iterator CppADS::Array<T>::end() const
{
    return const_iterator(m_data.get() + m_size);
};

template<typename T>
typename CppADS::Array<T>::const_iterator CppADS::Array<T>::cend() const
{
    return const_iterator(m_data.get() + m_size);
};

template<typename T>
typename CppADS::Array<T>::reverse_iterator CppADS::Array<T>::rbegin()
{
    return std::reverse_iterator<iterator>(m_data.get() + m_size);
};

template<typename T>
typename CppADS::Array<T>::const_reverse_iterator CppADS::Array<T>::rbegin() const
{
    return std::reverse_iterator<const_iterator>(m_data.get() + m_size);
};

template<typename T>
typename CppADS::Array<T>::const_reverse_iterator CppADS::Array<T>::crbegin() const
{
    return std::reverse_iterator<const_iterator>(m_data.get() + m_size);
};

template<typename T>
typename CppADS::Array<T>::reverse_iterator CppADS::Array<T>::rend()
{
    return std::reverse_iterator<iterator>(m_data.get());
};

template<typename T>
typename CppADS::Array<T>::const_reverse_iterator CppADS::Array<T>::rend() const
{
    return std::reverse_iterator<const_iterator>(m_data.get());
};

template<typename T>
typename CppADS::Array<T>::const_reverse_iterator CppADS::Array<T>::crend() const
{
    return std::reverse_iterator<const_iterator>(m_data.get());
}

#endif //ARRAY_H
