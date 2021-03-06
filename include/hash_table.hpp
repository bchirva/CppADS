#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "container.hpp"
#include "array.hpp"
#include "forward_list.hpp"

#include <functional>
#include <memory>

namespace CppADS
{
    /// @brief Hash table class
    /// @tparam K hashed key type
    /// @tparam T stored value type
    template <typename Key, typename T>
    class HashTable : public IContainer
    {
    public:
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        class iterator;
        class const_iterator;

        HashTable() = default;                                        ///< Default contructor
        HashTable(const HashTable& copy);                               ///< Copy contructor
        HashTable(HashTable&& move);                                    ///< Move contructor
        HashTable(std::initializer_list<value_type> init_list);   ///< Contructor from initializer list

        HashTable& operator=(const HashTable& copy);                    ///< Copy assignment operator
        HashTable& operator=(HashTable&& move);                         ///< Move assignment operator

        ~HashTable() = default;                                       ///< Destructor

        /// @name Capacity
        /// @{

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Get current number of buckets
        /// @return number of buckets
        size_t bucket_count() const;

        /// @brief Get current maximum number of elements per bucket
        /// @return maximum number of elements per bucket
        size_t max_load_factor() const;

        /// @}
        /// @name Hash policy
        /// @{

        /// @brief Get current maximum number of elements per bucket
        /// @param load_factor new maximum number of elements per bucket
        void set_load_factor(size_t load_factor);

        /// @}
        /// @name Modifiers
        /// @{

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Insert value to container
        /// @param pair key-value pair to insert
        void insert(const value_type& pair);
        /// @brief Insert value to container
        /// @param pair key-value pair to insert
        void insert(value_type&& pair);

        /// @brief Remove values from container
        /// @param key position of item to delete
        void remove(const key_type& key);

        /// @}
        /// @name Accesors
        /// @{

        /// @brief Access to item
        /// @param key item position
        /// @return reference to value
        mapped_type& operator[](const key_type& key);

        /// @brief Access to item
        /// @param key item position
        /// @return reference to value
        const mapped_type& operator[](const key_type& key) const;

        /// @brief Search for first item equal value
        /// @param key value search for
        /// @return iterator to found item (end if item not found)
        iterator find(const key_type& key);

        /// @brief Search for first item equal value
        /// @param key value search for
        /// @return iterator to found item (end if item not found)
        const_iterator find(const key_type& key) const;

        /// @}
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

        /// @}

        bool operator==(const HashTable<Key, T>& rhs) const;
        bool operator!=(const HashTable<Key, T>& rhs) const;

    private:
        using Bucket = CppADS::ForwardList<value_type>;
        CppADS::Array<Bucket> m_buckets {Bucket{}};

        size_t m_size { 0 };
        size_t m_max_load_factor { 1 };

        inline size_t calc_address(Key key) const;
        void rehash();
    };

    template<typename Key, typename T>
    /// @brief Read-write iterator for List container
    class HashTable<Key, T>::iterator : public std::iterator<std::forward_iterator_tag, value_type>
    {
    private:
        HashTable<Key, T>* m_container;
        typename Array<Bucket>::iterator m_bucket_it;
        typename Bucket::iterator        m_cell_it;

        inline bool is_end_of_bucket()
        {
            return (m_cell_it == m_bucket_it->end() && m_bucket_it != (m_container->m_buckets.end()--));
        }

    public:
        iterator(typename Array<Bucket>::iterator bucket_it,
                 typename Bucket::iterator cell_it,
                 HashTable<Key,T>* container)
            : m_container(container), m_bucket_it(bucket_it), m_cell_it(cell_it)
        {
            if (is_end_of_bucket())
                this->operator++();
        }
        ~iterator() {
            m_bucket_it = nullptr;
            m_cell_it = nullptr;
        }

        HashTable<Key,T>::reference operator*() {
            return m_cell_it.operator*();
        }
        HashTable<Key,T>::pointer operator->() {
            return m_cell_it.operator->();
        }

        iterator& operator++() {
            do
            {
                if (is_end_of_bucket())
                {
                    m_bucket_it++;
                    m_cell_it = m_bucket_it->begin();
                }
                else
                    m_cell_it++;
            }
            while (is_end_of_bucket());
            return *this;
        }
        iterator& operator++(int) {
            do
            {
                if (is_end_of_bucket())
                {
                    m_bucket_it++;
                    m_cell_it = m_bucket_it->begin();
                }
                else
                    m_cell_it++;
            }
            while (is_end_of_bucket());
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return (m_bucket_it == rhs.m_bucket_it && m_cell_it == rhs.m_cell_it);
        }
        bool operator!=(const iterator& rhs) const {
            return !(this->operator==(rhs));
        }
    };

    template<typename Key, typename T>
    /// @brief Read-only iterator for List container
    class HashTable<Key, T>::const_iterator : public std::iterator<std::forward_iterator_tag, value_type>
    {
    private:
        const HashTable<Key, T>* m_container;
        typename Array<Bucket>::const_iterator m_bucket_it;
        typename Bucket::const_iterator        m_cell_it;

        inline bool is_end_of_bucket()
        {
            return (m_cell_it == m_bucket_it->end() && m_bucket_it != (m_container->m_buckets.end()--));
        }

    public:
        const_iterator(typename Array<Bucket>::const_iterator bucket_it,
                       typename Bucket::const_iterator cell_it,
                       const HashTable<Key, T>* container)
            : m_container(container), m_bucket_it(bucket_it), m_cell_it(cell_it)
        {
            if (is_end_of_bucket())
                this->operator++();
        }
        ~const_iterator() {
            m_bucket_it = nullptr;
            m_cell_it = nullptr;
        }

        HashTable<Key,T>::const_reference operator*() {
            return m_cell_it.operator*();
        }
        HashTable<Key,T>::const_pointer operator->() {
            return m_cell_it.operator->();
        }

        const_iterator& operator++() {
            do
            {
                if (is_end_of_bucket())
                {
                    m_bucket_it++;
                    m_cell_it = m_bucket_it->begin();
                }
                else
                    m_cell_it++;
            }
            while (is_end_of_bucket());
            return *this;
        }
        const_iterator& operator++(int) {
            do
            {
                if (is_end_of_bucket())
                {
                    m_bucket_it++;
                    m_cell_it = m_bucket_it.begin();
                }
                else
                    m_cell_it++;
            }
            while (is_end_of_bucket());
            return *this;
        }

        bool operator==(const const_iterator& rhs) const {
            return (m_bucket_it == rhs.m_bucket_it && m_cell_it == rhs.m_cell_it);
        }
        bool operator!=(const const_iterator& rhs) const {
            return !(this->operator==(rhs));
        }
    };
}

template<typename Key, typename T>
CppADS::HashTable<Key, T>::HashTable(const HashTable& copy)
    : m_buckets(copy.m_buckets), m_size(copy.m_size), m_max_load_factor(copy.m_max_load_factor)
{}

template<typename Key, typename T>
CppADS::HashTable<Key, T>::HashTable(HashTable&& move)
    : m_buckets(std::move(move.m_buckets)), m_size(std::move(move.m_size)), m_max_load_factor(move.m_max_load_factor)
{
    move.m_size = 0;
}

template<typename Key, typename T>
CppADS::HashTable<Key, T>::HashTable(std::initializer_list<value_type> init_list)
{
    for(auto it = init_list.begin(); it != init_list.end(); it++)
        insert(*it);
}

template<typename Key, typename T>
CppADS::HashTable<Key, T>& CppADS::HashTable<Key, T>::operator=(const HashTable& copy)
{
    clear();
    m_buckets = copy.m_buckets;
    m_size = copy.m_size;
    m_max_load_factor = copy.m_max_load_factor;
    return *this;
}

template<typename Key, typename T>
CppADS::HashTable<Key, T>& CppADS::HashTable<Key, T>::operator=(HashTable&& move)
{
    m_buckets = std::move(move.m_buckets);
    m_size = std::move(move.m_size);
    m_max_load_factor = std::move(move.m_max_load_factor);
    move.m_size = 0;
    return *this;
}

template<typename Key, typename T>
size_t CppADS::HashTable<Key, T>::size() const
{
    return m_size;
}

template<typename Key, typename T>
size_t CppADS::HashTable<Key, T>::bucket_count() const
{
    return m_buckets.size();
}

template<typename Key, typename T>
size_t CppADS::HashTable<Key, T>::max_load_factor() const
{
    return m_max_load_factor;
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::set_load_factor(size_t load_factor)
{
    m_max_load_factor = load_factor;

    if (bucket_count() != 0 && ((size() / bucket_count()) > max_load_factor()))
        rehash();
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::clear()
{
    m_buckets = {Bucket{}};
    m_size = 0;
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::rehash()
{
    size_t old_size = m_buckets.size();
    CppADS::Array<Bucket> old(std::move(m_buckets));    
    m_buckets.reserve(old_size * 2 + 1);
    while(m_buckets.size() < m_buckets.capacity())
        m_buckets.push_back(Bucket{});

    for(typename CppADS::Array<Bucket>::iterator bucket = old.begin(); bucket != old.end(); bucket++)
    {
        for(typename Bucket::iterator cell = (*bucket).begin(); cell != (*bucket).end(); cell++)
        {
            m_buckets[calc_address(cell->first)].push_back(std::move(*cell));
        }
    }
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::insert(const HashTable::value_type& pair)
{
    if ((m_buckets.size() == 0) || ((size() + 1) / m_buckets.size() > max_load_factor()))
        rehash();

    size_t address = calc_address(pair.first);
    auto item = m_buckets[address].begin();
    while(item != m_buckets[address].end())
    {
        if (item->first == pair.first)
            break;
        item++;
    }

    if(item == m_buckets[address].end())
    {
        m_buckets[address].push_back(pair);
        m_size++;

        if (m_buckets[address].size() > max_load_factor())
            rehash();
    }
    else
        item->second = pair.second;
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::insert(HashTable::value_type&& pair)
{
    if ((m_buckets.size() == 0) || ((size() + 1) / m_buckets.size() > max_load_factor()))
        rehash();

    size_t address = calc_address(pair.first);
    auto item = m_buckets[address].begin();
    while(item != m_buckets[address].end())
    {
        if (item->first == pair.first)
            break;
        item++;
    }

    if(item == m_buckets[address].end())
    {
        m_buckets[address].push_back(std::move(pair));
        m_size++;

        if (m_buckets[address].size() > max_load_factor())
            rehash();
    }
    else
        item->second = std::move(pair.second);
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::remove(const HashTable::key_type& key)
{
    size_t address = calc_address(key);

    auto item = m_buckets[address].begin();
    auto remove_after = m_buckets[address].before_begin();
    while(item != m_buckets[address].end())
    {
        if (item->first == key)
            break;
        item++;
        remove_after++;
    }
    if (item != m_buckets[address].end())
        m_buckets[address].remove_after(remove_after);

    m_size--;
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::mapped_type& CppADS::HashTable<Key, T>::operator[](const HashTable::key_type& key)
{
    size_t address = calc_address(key);

    auto bucket_it = m_buckets[address].begin();
    while (bucket_it != m_buckets[address].end())
    {
        if(bucket_it->first == key)
            break;
        bucket_it++;
    }
    if (bucket_it != m_buckets[address].end())
    {
        return (*bucket_it).second;
    }
    else
    {
        insert({key, T()});
        return (*find(key)).second;
    }
}

template<typename Key, typename T>
const typename CppADS::HashTable<Key, T>::mapped_type& CppADS::HashTable<Key, T>::operator[](const HashTable::key_type& key) const
{
    size_t address = calc_address(key);

    auto bucket_it = m_buckets[address].begin();
    while (bucket_it != m_buckets[address].end())
    {
        if(bucket_it->first == key)
            break;
        bucket_it++;
    }
    if (bucket_it != m_buckets[address].end())
    {
        return *(bucket_it);
    }
    else
    {
        insert({key, T()});
        return (*find(key)).second;
    }
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::iterator CppADS::HashTable<Key, T>::find(const HashTable::key_type& key)
{
    size_t address = calc_address(key);

    auto bucket_it = m_buckets[address].begin();
    while (bucket_it != m_buckets[address].end())
    {
        if(bucket_it->first == key)
            break;
        bucket_it++;
    }
    if (bucket_it != m_buckets[address].end())
        return iterator((m_buckets.begin() + address), bucket_it, this);
    else
        return end();
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::const_iterator CppADS::HashTable<Key, T>::find(const HashTable::key_type& key) const
{
    size_t address = calc_address(key);

    auto bucket_it = m_buckets[address].begin();
    while (bucket_it != m_buckets[address].end())
    {
        if(bucket_it->first == key)
            break;
        bucket_it++;
    }
    if (bucket_it != m_buckets[address].end())
        return const_iterator((m_buckets.begin() + address), bucket_it, this);
    else
        return cend();
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::iterator CppADS::HashTable<Key, T>::begin() {
    return iterator(m_buckets.begin(), m_buckets.begin()->begin(), this);
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::const_iterator CppADS::HashTable<Key, T>::begin() const {
    return const_iterator(m_buckets.cbegin(), m_buckets.cbegin()->cbegin(), this);
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::const_iterator CppADS::HashTable<Key, T>::cbegin() const {
    return const_iterator(m_buckets.cbegin(), m_buckets.cbegin()->cbegin(), this);
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::iterator CppADS::HashTable<Key, T>::end() {
    return iterator(m_buckets.end()--, (m_buckets.end()--)->end(), this);
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::const_iterator CppADS::HashTable<Key, T>::end() const {
    return const_iterator(m_buckets.cend()--, (m_buckets.cend()--)->cend(), this);
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::const_iterator CppADS::HashTable<Key, T>::cend() const {
    return const_iterator(m_buckets.cend()--, (m_buckets.cend()--)->cend(), this);
}

template<typename Key, typename T>
bool CppADS::HashTable<Key, T>::operator==(const HashTable<Key, T> &rhs) const
{
    return m_buckets == rhs.m_buckets;
}

template<typename Key, typename T>
bool CppADS::HashTable<Key, T>::operator!=(const HashTable<Key, T> &rhs) const
{
    return !(operator==(rhs));
}

template<typename Key, typename T>
size_t CppADS::HashTable<Key, T>::calc_address(Key key) const
{
    return std::hash<Key>{}(key) % bucket_count();
}

#endif
