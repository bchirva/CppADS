#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include "container.hpp"

#include <memory>
#include <iterator>

namespace CppADS
{
    /// @brief Singly linked list
    /// @tparam T value type stored in the container
    template <class T>
    class ForwardList : public IContainer
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        class iterator;
        class const_iterator;

        ForwardList() = default;                                ///< Default constructor
        ForwardList(const ForwardList<T>& copy);                ///< Copy contructor
        ForwardList(ForwardList<T>&& move);                     ///< Move contructor
        ForwardList(std::initializer_list<T> init_list);        ///< Contructor from initializer ForwardList

        ForwardList& operator=(const ForwardList<T>& copy);     ///< Copy assignment operator
        ForwardList& operator=(ForwardList<T>&& move);          ///< Move assignment operator

        ~ForwardList() = default;                               ///< Destructor

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

        /// @brief Insert value to container
        /// @param value inserted value
        /// @param position position to insert
        void insert_after(const T& value, iterator position);
        /// @brief Insert value to container
        /// @param value inserted value
        /// @param position position to insert
        void insert_after(T&& value, iterator position);

        /// @brief Remove values from container
        /// @param position position of item to delete
        void remove_after(iterator position);

        /// @brief Add value to the tail of list
        /// @param value - added value
        void push_back(const T& value);
        /// @brief Add value to the tail of list
        /// @param value - added value
        void push_back(T&& value);

        /// @brief Add value to the head of list
        /// @param value - added value
        void push_front(const T& value);
        /// @brief Add value to the head of list
        /// @param value - added value
        void push_front(T&& value);

        /// @brief Remove first value of the list
        void pop_front();

        ///@}
        /// @name Accesors
        /// @{

        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        reference operator[](size_t index);
        /// @brief Access to item
        /// @param index item position
        /// @return const reference to value
        const_reference operator[](size_t index) const;

        /// @brief Access to the first item in list
        /// @return reference on first value
        reference front();
        /// @brief Access to the first item in list
        /// @return const reference on first value
        const_reference front() const;

        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return read-write iterator to found item (end if item not found)
        iterator find(const T& value);
        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return read-only iterator to found item (end if item not found)
        const_iterator find(const T& value) const;
        /// @}

        /// @brief Comparing two containers
        /// @return True if they equeal, othervise - false
        bool operator==(const ForwardList<T>& rhs) const;
        /// @brief Comparing two containers
        /// @return False if they equeal, othervise - true
        bool operator!=(const ForwardList<T>& rhs) const;

        /// @name Iterators
        /// @{

        /// @return read-write iterator to the first element of the container
        iterator begin();
        /// @return read-only iterator to the first element of the container
        const_iterator begin() const;
        /// @return read-only iterator to the first element of the container
        const_iterator cbegin() const;

        /// @return read-write iterator to the element before the first element of the container
        iterator before_begin();
        /// @return read-only iterator to the element before the first element of the container
        const_iterator before_begin() const;
        /// @return read-only iterator to the element before the first element of the container
        const_iterator cbefore_begin() const;

        /// @return read-write iterator to the element after the last element of the container
        iterator end();
        /// @return read-only iterator to the element after the last element of the container
        const_iterator end() const;
        /// @return read-only iterator to the element after the last element of the container
        const_iterator cend() const;
        /// @}

    private:
        struct Node;

        std::unique_ptr<Node> m_head = std::make_unique<Node>(nullptr, nullptr);    ///< Head of the list
        Node* m_tail = m_head.get();                                                ///< Pointer to the last element
        size_t m_size { 0 };                                                        ///< Count of elements
    };

    /// @brief Struct representing ForwardList's cell
    /// @tparam T value type stored in cell
    template<class T>
    struct ForwardList<T>::Node
    {
        std::unique_ptr<T> value { nullptr };           ///< Value of the cell          @private
        std::unique_ptr<Node> next { nullptr };         ///< Pointer to the next cell   @private

        Node(std::unique_ptr<T> _value, std::unique_ptr<Node> _next)
            : value(std::move(_value)), next(std::move(_next)) {}               ///< @private
        Node(T _value, std::unique_ptr<Node> _next)
            : value(std::make_unique<T>(_value)), next(std::move(_next)) {}     ///< @private
    };

    template<class T>
    /// @brief Read-write iterator for ForwardList container
    class ForwardList<T>::iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    private:
        ForwardList<T>::Node* m_ptr { nullptr };            ///< @private
        friend class ForwardList;

    public:
        iterator(Node* _ptr = nullptr) : m_ptr(_ptr) {};    ///< @private
        ~iterator() {m_ptr = nullptr;}

        ForwardList<T>::reference operator*() {
            if (m_ptr->value == nullptr)
                throw std::out_of_range("CppADS::ForwardList<T>::iterator::operator*: sentinel hasn't any value");
            return *(m_ptr->value);
        }
        ForwardList<T>::pointer operator->() {
            return m_ptr->value.get();
        }

        iterator& operator++() {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        iterator& operator++(int) {
            m_ptr = m_ptr->next.get();
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator!=(const iterator& rhs) const {
            return m_ptr != rhs.m_ptr;
        }
    };

    template<class T>
    /// @brief Read-only iterator for ForwardList container
    class ForwardList<T>::const_iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    private:
        ForwardList<T>::Node* m_ptr { nullptr };    ///< @private
        friend class ForwardList;

    public:
        const_iterator(Node* _ptr = nullptr) : m_ptr(_ptr) {}; ///< @private
        ~const_iterator() {m_ptr = nullptr;}

        ForwardList<T>::const_reference operator*() {
            if (m_ptr->value == nullptr)
                throw std::out_of_range("CppADS::ForwardList<T>::const_iterator::operator*: sentinel hasn't any value");
            return *(m_ptr->value);
        }
        ForwardList<T>::const_pointer operator->() {
            return m_ptr->value.get();
        }

        const_iterator& operator++() {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        const_iterator& operator++(int) {
            m_ptr = m_ptr->next.get();
            return *this;
        }

        bool operator==(const const_iterator& rhs) const {
            return m_ptr == rhs.m_ptr;
        }
        bool operator!=(const const_iterator& rhs) const {
            return m_ptr != rhs.m_ptr;
        }
    };
}

template<typename T>
CppADS::ForwardList<T>::ForwardList(const ForwardList<T>& copy)
{
    for (auto it = copy.begin(); it != copy.end(); it++)
        this->push_back(*it);
    m_size = copy.m_size;
}

template<typename T>
CppADS::ForwardList<T>::ForwardList(ForwardList<T>&& move)
{
    m_head = std::move(move.m_head);
    m_tail = std::move(move.m_tail);
    m_size = std::move(move.m_size);
    move.m_size = 0;
}

template<typename T>
CppADS::ForwardList<T>::ForwardList(std::initializer_list<T> init_list)
{
    for (auto it = init_list.begin(); it != init_list.end(); it++)
        this->push_back(*it);
    m_size = init_list.size();
}

template<typename T>
CppADS::ForwardList<T>& CppADS::ForwardList<T>::operator=(const ForwardList<T>& copy)
{
    clear();
    for (auto it = copy.begin(); it != copy.end(); it++)
        this->push_back(*it);
    m_size = copy.m_size;
    return *this;
}

template<typename T>
CppADS::ForwardList<T>& CppADS::ForwardList<T>::operator=(ForwardList<T>&& move)
{
    m_head = std::move(move.m_head);
    m_tail = std::move(move.m_tail);
    m_size = std::move(move.m_size);
    move.m_size = 0;
    return *this;
}

template<typename T>
void CppADS::ForwardList<T>::clear()
{
    m_head->next.reset(nullptr);
    m_tail = m_head.get();
    m_size = 0;
}

template<typename T>
size_t CppADS::ForwardList<T>::size() const
{
    return m_size;
}

template<typename T>
void CppADS::ForwardList<T>::insert_after(const T& value, iterator position)
{
    std::unique_ptr<Node> new_node = std::make_unique<Node>(value, std::move(position.m_ptr->next));
    position.m_ptr->next = std::move(new_node);
    m_size++;

    if(position.m_ptr->next->next == nullptr)
        m_tail = position.m_ptr->next.get();
}

template<typename T>
void CppADS::ForwardList<T>::insert_after(T&& value, iterator position)
{
    std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value), std::move(position.m_ptr->next));
    position.m_ptr->next = std::move(new_node);
    m_size++;

    if(position.m_ptr->next->next == nullptr)
        m_tail = position.m_ptr->next.get();
}

template<typename T>
void CppADS::ForwardList<T>::remove_after(iterator position)
{
    auto tmp = std::move(position.m_ptr->next->next);
    position.m_ptr->next = std::move(tmp);
    m_size--;

    if(position.m_ptr->next == nullptr)
        m_tail = position.m_ptr;
}

template<typename T>
void CppADS::ForwardList<T>::push_back(const T& value)
{
    insert_after(value, iterator(m_tail));
}

template<typename T>
void CppADS::ForwardList<T>::push_back(T&& value)
{
    insert_after(std::move(value), iterator(m_tail));
}

template<typename T>
void CppADS::ForwardList<T>::push_front(const T& value)
{
    insert_after(value, before_begin());
}

template<typename T>
void CppADS::ForwardList<T>::push_front(T&& value)
{
    insert_after(std::move(value), before_begin());
}

template<typename T>
void CppADS::ForwardList<T>::pop_front()
{
    remove_after(before_begin());
}

template<typename T>
typename CppADS::ForwardList<T>::iterator CppADS::ForwardList<T>::find(const T& value)
{
    auto it = begin();
    while(it != end())
    {
        if (*it == value)
            break;
        it++;
    }
    return it;
}

template<typename T>
typename CppADS::ForwardList<T>::const_iterator CppADS::ForwardList<T>::find(const T& value) const
{
    auto it = cbegin();
    while(it != cend())
    {
        if (*it == value)
            break;
        it++;
    }
    return it;
}

template<typename T>
typename CppADS::ForwardList<T>::reference CppADS::ForwardList<T>::operator[](size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::ForwardList<T>::operator[]: index is out of range");

    auto it = begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}

template<typename T>
typename CppADS::ForwardList<T>::const_reference CppADS::ForwardList<T>::operator[](size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::ForwardList<T>::operator[]: index is out of range");

    auto it = cbegin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}

template<typename T>
typename CppADS::ForwardList<T>::reference CppADS::ForwardList<T>::front()
{
    return *(begin());
}

template<typename T>
typename CppADS::ForwardList<T>::const_reference CppADS::ForwardList<T>::front() const
{
    return *(cbegin());
}

template<typename T>
bool CppADS::ForwardList<T>::operator==(const ForwardList<T>& rhs) const
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
bool CppADS::ForwardList<T>::operator!=(const ForwardList<T>& rhs) const
{
    return !(*this == rhs);
}

template<typename T>
typename CppADS::ForwardList<T>::iterator CppADS::ForwardList<T>::begin() {
    return iterator(m_head->next.get());
}

template<typename T>
typename CppADS::ForwardList<T>::const_iterator CppADS::ForwardList<T>::begin() const {
    return const_iterator(m_head->next.get());
}

template<typename T>
typename CppADS::ForwardList<T>::const_iterator CppADS::ForwardList<T>::cbegin() const {
    return const_iterator(m_head->next.get());
}

template<typename T>
typename CppADS::ForwardList<T>::iterator CppADS::ForwardList<T>::before_begin() {
    return iterator(m_head.get());
}

template<typename T>
typename CppADS::ForwardList<T>::const_iterator CppADS::ForwardList<T>::before_begin() const {
    return const_iterator(m_head.get());
}

template<typename T>
typename CppADS::ForwardList<T>::const_iterator CppADS::ForwardList<T>::cbefore_begin() const {
    return const_iterator(m_head.get());
}

template<typename T>
typename CppADS::ForwardList<T>::iterator CppADS::ForwardList<T>::end() {
    return iterator(nullptr);
}

template<typename T>
typename CppADS::ForwardList<T>::const_iterator CppADS::ForwardList<T>::end() const {
    return const_iterator(nullptr);
}

template<typename T>
typename CppADS::ForwardList<T>::const_iterator CppADS::ForwardList<T>::cend() const {
    return const_iterator(nullptr);
}

#endif //DOUBLEForwardList_H
