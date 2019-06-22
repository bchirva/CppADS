#ifndef ARRAY_H
#define ARRAY_H

#include "Container.hpp"

#include <cmath>
#include <memory>
#include <functional>
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
        Array(const Array<T>& copy);                ///< Copy contructor
        Array(Array<T>&& move);                     ///< Move contructor
        Array(std::initializer_list<T> init_list);  ///< Contructor from initializer list

        Array<T>& operator=(const Array<T>& copy);  ///< Copy assignment operator
        Array<T>& operator=(Array<T>&& move);       ///< Move assignment operator

        ~Array() = default;                         ///< Destructor

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Get reserved size for container's data
        /// @return Current array's capacity
        size_t capacity() const;

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
        /// @param iterator position to insert
        void insert(const T& value, iterator position);

        /// @brief Insert value to container
        /// @param value inserted value
        /// @param iterator position to insert
        void insert(T&& value, iterator position);

        /// @brief Remove values from container
        /// @param iterator position of item to delete
        void remove(size_t index);

        /// @brief Remove values from container
        /// @param iterator position of item to delete
        void remove(iterator position);

        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        T& operator[](size_t index);

        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        const T& operator[](size_t index) const;

        /// @brief Set function for reserved size calculation
        /// @param func function
        void setReserveFunc(std::function<size_t(size_t)>&& func);

        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return iterator to found item (end if item not found)
        iterator find(const T& value);

        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return iterator to found item (end if item not found)
        const_iterator find(const T& value) const;

        iterator begin() {
            return Iterator(m_data.get());
        };
        const_iterator begin() const {
            return ConstIterator(m_data.get());
        };
        const_iterator cbegin() const {
            return ConstIterator(m_data.get());
        };
        iterator end() {
            return Iterator(m_data.get() + m_size);
        };
        const_iterator end() const {
            return ConstIterator(m_data.get() + m_size);
        };
        const_iterator cend() const {
            return ConstIterator(m_data.get() + m_size);
        };
        reverse_iterator rbegin() {
            return std::reverse_iterator<Iterator>(m_data.get() + m_size);
        };
        const_reverse_iterator rbegin() const {
            return std::reverse_iterator<ConstIterator>(m_data.get() + m_size);
        };
        const_reverse_iterator crbegin() const {
            return std::reverse_iterator<ConstIterator>(m_data.get() + m_size);
        };
        reverse_iterator rend() {
            return std::reverse_iterator<Iterator>(m_data.get());
        };
        const_reverse_iterator rend() const {
            return std::reverse_iterator<ConstIterator>(m_data.get());
        };
        const_reverse_iterator crend() const {
            return std::reverse_iterator<ConstIterator>(m_data.get());
        };

        bool operator==(const Array<T>& rhs) const;
        bool operator!=(const Array<T>& rhs) const;

    private:
        std::unique_ptr<T[]> m_data { nullptr };      ///< Pointer to the data head on heap
        size_t m_size { 0 };                          ///< Array actual size
        size_t m_capacity { 0 };                      ///< Reserved size

        /// @brief Allocation size calculation function
        /// @param _size for which you need to reserve a space
        /// @return space to resererve
        std::function<size_t(size_t)> m_reserve_func = [](size_t _size) -> size_t {
            if (_size > 0)
            {
                int current_power = std::ceil(std::log2(_size));
                return std::pow(2, current_power);
            }
            else return 1;
        };
    };

    template<typename T>
    class Array<T>::Iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    private:
        T* m_ptr { nullptr };

    public:
        Iterator(T* src_ptr) : m_ptr(src_ptr) {}
        ~Iterator() {m_ptr = nullptr;}

        Array<T>::reference operator*() {
            return *m_ptr;
        }
        Array<T>::pointer operator->() {
            return m_ptr;
        }
        Array<T>::reference operator[](int AIndex) {
            return m_ptr[AIndex];
        }

        Iterator& operator++() {
            m_ptr++;
            return *this;
        }
        Iterator& operator--() {
            m_ptr--;;
            return *this;
        }
        Iterator& operator++(int) {
            m_ptr++;
            return *this;
        }
        Iterator& operator--(int) {
            m_ptr--;;
            return *this;
        }
        Iterator operator+(int AOffset){
            Iterator result(m_ptr);
            result.m_ptr += AOffset;
            return result;
        }
        Iterator operator-(int AOffset){
            Iterator result(m_ptr);
            result.m_ptr -= AOffset;
            return result;
        }

        bool operator==(const Iterator& rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator!=(const Iterator& rhs) const {
            return m_ptr != rhs.m_ptr;
        }
        bool operator>(const Iterator& rhs) const {
            return m_ptr > rhs.m_ptr;
        }
        bool operator<(const Iterator& rhs) const {
            return m_ptr < rhs.m_ptr;
        }
        bool operator>=(const Iterator& rhs) const {
            return m_ptr >= rhs.m_ptr;
        }
        bool operator<=(const Iterator& rhs) const {
            return m_ptr <= rhs.m_ptr;
        }
    };

    template<typename T>
    class Array<T>::ConstIterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    private:
        T* m_ptr { nullptr };

    public:
        ConstIterator(T* src_ptr) : m_ptr(src_ptr) {}
        ~ConstIterator() {m_ptr = nullptr;}

        Array<T>::const_reference operator*() {
            return *m_ptr;
        }
        Array<T>::const_pointer operator->() {
            return m_ptr;
        }
        Array<T>::const_reference operator[](int AIndex) {
            return m_ptr[AIndex];
        }

        ConstIterator& operator++() {
            m_ptr++;
            return *this;
        }
        ConstIterator& operator--() {
            m_ptr--;;
            return *this;
        }
        ConstIterator& operator++(int) {
            m_ptr++;
            return *this;
        }
        ConstIterator& operator--(int) {
            m_ptr--;;
            return *this;
        }
        ConstIterator operator+(int AOffset){
            ConstIterator result(m_ptr);
            result.m_ptr += AOffset;
            return result;
        }
        ConstIterator operator-(int AOffset){
            ConstIterator result(m_ptr);
            result.m_ptr -= AOffset;
            return result;
        }

        bool operator==(const ConstIterator& rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator!=(const ConstIterator& rhs) const {
            return m_ptr != rhs.m_ptr;
        }
        bool operator>(const ConstIterator& rhs) const {
            return m_ptr > rhs.m_ptr;
        }
        bool operator<(const ConstIterator& rhs) const {
            return m_ptr < rhs.m_ptr;
        }
        bool operator>=(const ConstIterator& rhs) const {
            return m_ptr >= rhs.m_ptr;
        }
        bool operator<=(const ConstIterator& rhs) const {
            return m_ptr <= rhs.m_ptr;
        }
    };

}

template<typename T>
CppADS::Array<T>::Array(const Array<T>& copy)
{
    m_size = copy.m_size;
    m_capacity = copy.m_capacity;
    m_data = std::make_unique<T[]>(m_capacity);
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = copy.m_data[i];
    }
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
    m_size = init_list.size();
    m_capacity = m_reserve_func(m_size);
    m_data = std::make_unique<T[]>(m_capacity);
    int i = 0;
    for(auto it = init_list.begin(); it != init_list.end(); it++, i++)
    {
        m_data[i] = *it;
    }
}

template<typename T>
CppADS::Array<T>& CppADS::Array<T>::operator=(const Array<T>& copy)
{
    m_size = copy.m_size;
    m_capacity = copy.m_capacity;
    m_data = std::make_unique<T[]>(m_capacity);
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
    {
        m_capacity = m_reserve_func(m_size + 1);
        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_capacity);
        auto tmp_it     = tmp.get();
        auto tmp_end    = tmp.get() + m_size + 1;
        auto insert_it  = begin() + index;
        auto data_it    = begin();

        while (tmp_it != tmp_end)
        {
            if (data_it == insert_it)
            {
                *tmp_it = value;
                tmp_it++;
                insert_it = nullptr;
                continue;
            }

            *tmp_it = std::move(*data_it);
            tmp_it++;
            data_it++;
        }
        m_data = std::move(tmp);
    }
    else
    {
        auto it = end();
        auto insert_it = begin() + index;
        while (it != insert_it)
        {
            *it = std::move(*(it - 1));
            it--;
        }
        *insert_it = value;
     }

    m_size++;
}

template<typename T>
void CppADS::Array<T>::insert(T&& value, size_t index)
{
    if (index > m_size)
        throw std::out_of_range("CppADS::Array<T>::insert: index is out of range");

    if (m_capacity == m_size)
    {
        m_capacity = m_reserve_func(m_size + 1);
        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_capacity);
        auto tmp_it     = tmp.get();
        auto tmp_end    = tmp.get() + m_size + 1;
        auto insert_it  = begin() + index;
        auto data_it    = begin();

        while (tmp_it != tmp_end)
        {
            if (data_it == insert_it)
            {
                *tmp_it = std::move(value);
                tmp_it++;
                insert_it = nullptr;
                continue;
            }

            *tmp_it = std::move(*data_it);
            tmp_it++;
            data_it++;
        }
        m_data = std::move(tmp);
    }
    else
    {
        auto it = end();
        auto insert_it = begin() + index;
        while (it != insert_it)
        {
            *it = std::move(*(it - 1));
            it--;
        }
        *insert_it = std::move(value);
     }

    m_size++;
}

template<typename T>
void CppADS::Array<T>::insert(const T& value, iterator position)
{
    if (position > end() || position < begin())
         throw std::out_of_range("CppADS::Array<T>::insert: iterator is invalid");

    if (m_capacity == m_size)
    {
        m_capacity = m_reserve_func(m_size + 1);
        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_capacity);
        auto tmp_it     = tmp.get();
        auto tmp_end    = tmp.get() + m_size + 1;
        auto data_it    = begin();

        while (tmp_it != tmp_end)
        {
            if (data_it == position)
            {
                *tmp_it = value;
                tmp_it++;
                position = nullptr;
                continue;
            }

            *tmp_it = std::move(*data_it);
            tmp_it++;
            data_it++;
        }
        m_data = std::move(tmp);
    }
    else
    {
        auto it = end();
        while (it != position)
        {
            *it = std::move(*(it - 1));
            it--;
        }
        *position = value;
     }

    m_size++;
}

template<typename T>
void CppADS::Array<T>::insert(T&& value, iterator position)
{
    if (position > end() || position < begin())
         throw std::out_of_range("CppADS::Array<T>::insert: iterator is invalid");

    if (m_capacity == m_size)
    {
        m_capacity = m_reserve_func(m_size + 1);
        std::unique_ptr<T[]> tmp = std::make_unique<T[]>(m_capacity);
        auto tmp_it     = tmp.get();
        auto tmp_end    = tmp.get() + m_size + 1;
        auto data_it    = begin();

        while (tmp_it != tmp_end)
        {
            if (data_it == position)
            {
                *tmp_it = std::move(value);
                tmp_it++;
                position = nullptr;
                continue;
            }

            *tmp_it = std::move(*data_it);
            tmp_it++;
            data_it++;
        }
        m_data = std::move(tmp);
    }
    else
    {
        auto it = end();
        while (it != position)
        {
            *it = std::move(*(it - 1));
            it--;
        }
        *position = std::move(value);
     }

    m_size++;
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

template<typename T>
void CppADS::Array<T>::setReserveFunc(std::function<size_t(size_t)>&& func)
{
    m_reserve_func = std::move(func);
}

template<typename T>
typename CppADS::Array<T>::iterator CppADS::Array<T>::find(const T& value)
{
    auto it = begin();
    while(it != end())
    {
        if (*it == value) break;
        ++it;
    }
    return it;
}

template<typename T>
typename CppADS::Array<T>::const_iterator CppADS::Array<T>::find(const T& value) const
{
    auto it = cbegin();
    while(it != cend())
    {
        if (*it == value) break;
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

#endif //ARRAY_H
