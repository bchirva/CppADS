#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "container.hpp"
#include "array.hpp"
#include "list.hpp"

#include <memory>
#include <functional>

template <typename T>
long hash(T key);

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
        using reference = mapped_type&;
        using const_reference = const mapped_type&;
        using pointer = mapped_type*;
        using const_pointer = const mapped_type*;

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

        ///
        void rehash();

        /// @brief Insert value to container
        /// @param key position to insert
        /// @param value inserted value
        void insert(const key_type& key, const mapped_type& value);
        /// @brief Insert value to container
        /// @param key position to insert
        /// @param value inserted value
        void insert(const key_type& key, mapped_type&& value);

        /// @brief Remove values from container
        /// @param key position of item to delete
        void remove(const key_type& key);

        /// @}
        /// @name Accesors
        /// @{

        /// @brief Access to item
        /// @param key item position
        /// @return reference to value
        reference operator[](const key_type& key);

        /// @brief Access to item
        /// @param key item position
        /// @return reference to value
        const_reference operator[](const key_type& key) const;

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

    private:
        using Bucket = CppADS::List<value_type>;
        CppADS::Array<Bucket> m_buckets {};

        size_t m_size { 0 };
        size_t m_max_load_factor { 3 };
    };

/*
    template<typename Key, typename T>
    /// @brief Read-write iterator for List container
    class HashTable<Key, T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        //List<T>::Node* m_ptr { nullptr };       ///< @private


    public:
        //iterator(Node* _ptr = nullptr) : m_ptr(_ptr) {};    ///< @private
        ~iterator() {m_ptr = nullptr;}

        List<T>::reference operator*() {

        }
        List<T>::pointer operator->() {

        }

        iterator& operator++() {

            return *this;
        }
        iterator& operator--() {

            return *this;
        }
        iterator& operator++(int) {

            return *this;
        }
        iterator& operator--(int) {

            return *this;
        }

        bool operator==(const iterator& rhs) const {
            //return m_ptr == rhs.m_ptr;
        }
        bool operator!=(const iterator& rhs) const {
            //return m_ptr != rhs.m_ptr;
        }
    };

    template<typename Key, typename T>
    /// @brief Read-only iterator for List container
    class HashTable<Key, T>::const_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        //List<T>::Node* m_ptr { nullptr };       ///< @private

    public:
        const_iterator(Node* _ptr = nullptr) : m_ptr(_ptr) {}; ///< @private
        ~const_iterator() {m_ptr = nullptr;}

        List<T>::const_reference operator*() {
        }
        List<T>::const_pointer operator->() {
        }

        const_iterator& operator++() {
            return *this;
        }
        const_iterator& operator--() {
            return *this;
        }
        const_iterator& operator++(int) {
            return *this;
        }
        const_iterator& operator--(int) {
            return *this;
        }

        bool operator==(const const_iterator& rhs) const {

        }
        bool operator!=(const const_iterator& rhs) const {

        }
    };
*/
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
CppADS::HashTable<Key, T>::HashTable(std::initializer_list<HashTable::value_type> init_list)
{
    for(auto it = init_list.begin(); it != init_list.end(); it++)
        insert(it->first, std::move(it->second));
}

template<typename Key, typename T>
CppADS::HashTable<Key, T>& CppADS::HashTable<Key, T>::operator=(const HashTable& copy)
{
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
    m_buckets.clear();
    m_size = 0;
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::rehash()
{

}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::insert(const HashTable::key_type& key, const HashTable::mapped_type& value)
{
    long hashed_key = hash(key);
    size_t address = std::abs(hashed_key) % m_buckets.size();

    auto item = m_buckets[address].find(key);
    if(item != m_buckets[address].end())
        m_buckets[address].push_back(value);
    else
        item->second = value;

    size++;
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::insert(const HashTable::key_type& key, HashTable::mapped_type&& value)
{
    long hashed_key = hash(key);
    size_t address = std::abs(hashed_key) % m_buckets.size();

    auto item = m_buckets[address].find(key);
    if(item != m_buckets[address].end())
        m_buckets[address].push_back(value);
    else
        item->second = std::move(value);

    size++;
}

template<typename Key, typename T>
void CppADS::HashTable<Key, T>::remove(const HashTable::key_type& key)
{
    long hashed_key = hash(key);
    size_t address = std::abs(hashed_key) % m_buckets.size();

    auto item = m_buckets[address].find(key);
    if (item != m_buckets[address].end())
        m_buckets[address].remove(item);

    size--;
}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::reference CppADS::HashTable<Key, T>::operator[](const HashTable::key_type& key)
{

}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::const_reference CppADS::HashTable<Key, T>::operator[](const HashTable::key_type& key) const
{

}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::iterator CppADS::HashTable<Key, T>::find(const HashTable::key_type& key)
{

}

template<typename Key, typename T>
typename CppADS::HashTable<Key, T>::const_iterator CppADS::HashTable<Key, T>::find(const HashTable::key_type& key) const
{

}

#endif
