#ifndef LIST_HPP
#define LIST_HPP

#include "Container.hpp"

#include <memory>
#include <iterator>

namespace CppADS
{
    template <class T>
    /// @brief Doubly linked list
    class List : public IContainer
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

        List();                                     ///< Default constructor
        List(const List<T>& copy);                  ///< Copy contructor
        List(List<T>&& move);                       ///< Move contructor
        List(std::initializer_list<T> init_list);   ///< Contructor from initializer List

        List& operator=(const List<T>& copy);       ///< Copy assignment operator
        List& operator=(List<T>&& move);            ///< Move assignment operator

        ~List() = default;                          ///< Destructor

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Insert value to container
        /// @param value inserted value
        /// @param iterator position to insert
        void insert(const T& value, iterator position);

        /// @brief Insert value to container
        /// @param value inserted value
        /// @param iterator position to insert
        void insert(T&& value, iterator position);

        /// @brief Remove values from container
        /// @param iterator position of item to delet
        void remove(iterator position);

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

        /// @brief Remove first value of the list
        void pop_back();

        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        reference operator[](size_t index);

        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        const_reference operator[](size_t index) const;

        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return iterator to found item (end if item not found)
        iterator find(const T& value);

        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return iterator to found item (end if item not found)
        const_iterator find(const T& value) const;

        iterator begin() {
            return iterator(m_sentinel->next.get());
        }
        const_iterator begin() const {
            return const_iterator(m_sentinel->next.get());
        }
        const_iterator cbegin() const {
            return const_iterator(m_sentinel->next.get());
        }
        iterator end() {
            return iterator(m_sentinel.get());
        }
        const_iterator end() const {
            return const_iterator(m_sentinel.get());
        }
        const_iterator cend() const {
            return const_iterator(m_sentinel.get());
        }
        reverse_iterator rbegin() {
            return std::reverse_iterator<iterator>();
        };
        const_reverse_iterator rbegin() const {
            return std::reverse_iterator<const_iterator>();
        };
        const_reverse_iterator crbegin() const {
            return std::reverse_iterator<const_iterator>();
        };
        reverse_iterator rend() {
            return std::reverse_iterator<iterator>();
        };
        const_reverse_iterator rend() const {
            return std::reverse_iterator<const_iterator>();
        };
        const_reverse_iterator crend() const {
            return std::reverse_iterator<const_iterator>();
        };

        bool operator==(const List<T>& rhs) const;
        bool operator!=(const List<T>& rhs) const;

    private:
        struct Node;

        std::shared_ptr<Node> m_sentinel = std::make_shared<Node>(nullptr, nullptr, nullptr);
        size_t m_size { 0 };
    };

    template<class T>
    struct List<T>::Node
    {
        std::unique_ptr<T> value   { nullptr };
        std::shared_ptr<Node> next { nullptr };
        std::shared_ptr<Node> prev { nullptr };
        Node(std::unique_ptr<T> _value, std::shared_ptr<Node> _next, std::shared_ptr<Node> _prev)
            : value(std::move(_value)), next(_next), prev(_prev) {}
        Node(T _value, std::shared_ptr<Node> _next, std::shared_ptr<Node> _prev)
            : value(std::make_unique<T>(_value)), next(_next), prev(_prev) {}
    };

    template<class T>
    class List<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        List<T>::Node* m_ptr { nullptr };
        friend class List;

    public:
        iterator(Node* _ptr = nullptr) : m_ptr(_ptr) {};
        ~iterator() {m_ptr = nullptr;}

        List<T>::reference operator*() {
            return *(m_ptr->value);
        }
        List<T>::pointer operator->() {
            return m_ptr->value;
        }

        iterator& operator++() {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        iterator& operator--() {
            m_ptr = m_ptr->prev.get();
            return *this;
        }
        iterator& operator++(int) {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        iterator& operator--(int) {
            m_ptr = m_ptr->prev.get();
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
    class List<T>::const_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    private:
        List<T>::Node* m_ptr { nullptr };
        friend class List;

    public:
        const_iterator(Node* _ptr = nullptr) : m_ptr(_ptr) {};
        ~const_iterator() {m_ptr = nullptr;}

        List<T>::const_reference operator*() {
            return *(m_ptr->value);
        }
        List<T>::const_pointer operator->() {
            return m_ptr->value.get();
        }

        const_iterator& operator++() {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        const_iterator& operator--() {
            m_ptr = m_ptr->prev.get();
            return *this;
        }
        const_iterator& operator++(int) {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        const_iterator& operator--(int) {
            m_ptr = m_ptr->prev.get();
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
CppADS::List<T>::List()
{
    m_sentinel->next = m_sentinel;
    m_sentinel->prev = m_sentinel;
}

template<typename T>
CppADS::List<T>::List(const List<T>& copy)
    : List()
{
    for (auto it = copy.begin(); it != copy.end(); it++)
        this->insert(*it, this->end());
    m_size = copy.m_size;
}

template<typename T>
CppADS::List<T>::List(List<T>&& move)
{
    m_sentinel = std::move(move.m_sentinel);
    m_size = std::move(move.m_size);
    move.m_size = 0;
}

template<typename T>
CppADS::List<T>::List(std::initializer_list<T> init_list)
    : List()
{
    for (auto it = init_list.begin(); it != init_list.end(); it++)
        this->insert(*it, this->end());
    m_size = init_list.size();
}

template<typename T>
CppADS::List<T>& CppADS::List<T>::operator=(const List<T>& copy)
{
    clear();
    for (auto it = copy.begin(); it != copy.end(); it++)
        this->insert(*it, this->end());
    m_size = copy.m_size;
    return *this;
}

template<typename T>
CppADS::List<T>& CppADS::List<T>::operator=(List<T>&& move)
{
    clear();
    m_sentinel = std::move(move.m_sentinel);
    m_size = std::move(move.m_size);
    move.m_size = 0;
    return *this;
}

template<typename T>
void CppADS::List<T>::clear()
{
    while(size() != 0)
        remove(end());
}

template<typename T>
size_t CppADS::List<T>::size() const
{
    return m_size;
}

template<typename T>
void CppADS::List<T>::insert(const T& value, iterator position)
{
    auto prev = position;
    prev--;
    std::shared_ptr<Node> node = std::make_shared<Node>(value, prev.m_ptr->next, position.m_ptr->prev);
    prev.m_ptr->next = node;
    position.m_ptr->prev = node;

    m_size++;
}

template<typename T>
void CppADS::List<T>::insert(T&& value, iterator position)
{
    auto prev = position;
    prev--;
    std::shared_ptr<Node> node = std::make_shared<Node>(value, prev.m_ptr->next, position.m_ptr->prev);
    prev.m_ptr->next = node;
    position.m_ptr->prev = node;

    m_size++;
}

template<typename T>
void CppADS::List<T>::remove(iterator position)
{
    auto next = position.m_ptr->next;
    auto prev = position.m_ptr->prev;
    next->prev = prev;
    prev->next = next;
    m_size--;
}

template<typename T>
void CppADS::List<T>::push_back(const T& value)
{
    this->insert(value, this->end());
}

template<typename T>
void CppADS::List<T>::push_back(T&& value)
{
    this->insert(std::move(value), this->end());
}

template<typename T>
void CppADS::List<T>::push_front(const T& value)
{
    this->insert(value, this->begin());
}

template<typename T>
void CppADS::List<T>::push_front(T&& value)
{
    this->insert(std::move(value), begin());
}

template<typename T>
void CppADS::List<T>::pop_front()
{
    this->remove(this->begin());
}

template<typename T>
void CppADS::List<T>::pop_back()
{
    this->remove((this->end()--));
}

template<typename T>
typename CppADS::List<T>::iterator CppADS::List<T>::find(const T& value)
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
typename CppADS::List<T>::const_iterator CppADS::List<T>::find(const T& value) const
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
typename CppADS::List<T>::reference CppADS::List<T>::operator[](size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::List<T>::operator[]: index is out of range");

    auto it = begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}

template<typename T>
typename CppADS::List<T>::const_reference CppADS::List<T>::operator[](size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range("CppADS::List<T>::operator[]: index is out of range");

    auto it = cbegin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}

template<typename T>
typename CppADS::List<T>::reference CppADS::List<T>:: front()
{
    return *(begin());
}

template<typename T>
typename CppADS::List<T>::const_reference CppADS::List<T>:: front() const
{
    return *(cbegin());
}

template<typename T>
typename CppADS::List<T>::reference CppADS::List<T>:: back()
{
    return *(end()--);
}

template<typename T>
typename CppADS::List<T>::const_reference CppADS::List<T>:: back() const
{
    return *(cend()--);
}

template<class T>
bool CppADS::List<T>::operator==(const List<T>& rhs) const
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

template<class T>
bool CppADS::List<T>::operator!=(const List<T>& rhs) const
{
    return !(*this == rhs);
}


#endif //DOUBLEList_H
