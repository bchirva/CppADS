#ifndef DOUBLEForwardList_H
#define DOUBLEForwardList_H

#include "Container.hpp"

#include <memory>
#include <iterator>

namespace CppADS
{
    template <class T>
    /// @brief Singly linked list
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

        ForwardList() = default;                                  ///< Default constructor
        ForwardList(const ForwardList<T>& copy);                  ///< Copy contructor
        ForwardList(ForwardList<T>&& move);                       ///< Move contructor
        ForwardList(std::initializer_list<T> init_ForwardList);   ///< Contructor from initializer ForwardList

        ForwardList& operator=(const ForwardList<T>& copy);       ///< Copy assignment operator
        ForwardList& operator=(ForwardList<T>&& move);            ///< Move assignment operator

        ~ForwardList() = default;                                 ///< Destructor

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Insert value to container
        /// @param value inserted value
        /// @param iterator position to insert
        void insert(const T& value, iterator position_after);

        /// @brief Insert value to container
        /// @param value inserted value
        /// @param iterator position to insert
        void insert(T&& value, iterator position_after);

        void push_back(const T& value);

        void push_back(T&& value);

        void push_front(const T& value);

        void push_front(T&& value);

        /// @brief Remove values from container
        /// @param iterator position of item to delet
        void remove(iterator position_after);

        void remove_back();

        void remove_front();

        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        T& operator[](size_t index);

        /// @brief Access to item
        /// @param index item position
        /// @return reference to value
        const T& operator[](size_t index) const;

        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return iterator to found item (end if item not found)
        iterator find(const T& value);

        /// @brief Search for first item equal value
        /// @param value value search for
        /// @return iterator to found item (end if item not found)
        const_iterator find(const T& value) const;

        iterator begin() {
            return iterator(m_head.get());
        }
        const_iterator begin() const {
            return const_iterator(m_head.get());
        }
        const_iterator cbegin() const {
            return const_iterator(m_head.get());
        }
        iterator end() {
            return iterator(nullptr);
        }
        const_iterator end() const {
            return const_iterator(nullptr);
        }
        const_iterator cend() const {
            return const_iterator(nullptr);
        }

        bool operator==(const ForwardList<T>& rhs) const;
        bool operator!=(const ForwardList<T>& rhs) const;

    private:
        struct Node
        {
            T value {};
            std::unique_ptr<Node> next { nullptr };
            Node(T _value, std::unique_ptr<Node> _next)
                : value(_value), next(std::move(_next)) {}
        };

        std::unique_ptr<Node> m_head { nullptr };
        Node* m_tail { nullptr };
        size_t m_size { 0 };
    };

    template<class T>
    class ForwardList<T>::iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    private:
        ForwardList<T>::Node* m_ptr { nullptr };
        friend class ForwardList;

    public:
        iterator(Node* _ptr) : m_ptr(_ptr) {};
        ~iterator() {m_ptr = nullptr;}

        ForwardList<T>::reference operator*() {
            return m_ptr->value;
        }
        ForwardList<T>::pointer operator->() {
            return &(m_ptr->value);
        }

        iterator& operator++() {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        iterator& operator--() {
            m_ptr = m_ptr->prev->get();
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
    class ForwardList<T>::const_iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    private:
        ForwardList<T>::Node* m_ptr { nullptr };
        friend class ForwardList;

    public:
        const_iterator(Node* _ptr) : m_ptr(_ptr) {};
        ~const_iterator() {m_ptr = nullptr;}

        ForwardList<T>::const_reference operator*() {
            return m_ptr->value;
        }
        ForwardList<T>::const_pointer operator->() {
            return &(m_ptr->value);
        }

        const_iterator& operator++() {
            m_ptr = m_ptr->next.get();
            return *this;
        }
        const_iterator& operator--() {
            m_ptr = m_ptr->prev->get();
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

        friend class ForwardList;
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
    while(begin() != end())
        remove(end());
}

template<typename T>
size_t CppADS::ForwardList<T>::size() const
{
    return m_size;
}

template<typename T>
void CppADS::ForwardList<T>::insert(const T& value, iterator position_after)
{
    std::unique_ptr<Node> new_node = std::make_unique<Node>(value, std::move(position_after.m_ptr->next));
    position_after.m_ptr->next= std::move(new_node);
    m_size++;

    if(position_after.m_ptr->next->next == nullptr)
        m_tail = position_after.m_ptr->next.get();
}

template<typename T>
void CppADS::ForwardList<T>::insert(T&& value, iterator position_after)
{
    std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value), std::move(position_after->next));
    position_after->next = std::move(new_node);
    m_size++;

    if(position_after->next->next == nullptr)
        m_tail = position_after->next.get();
}

template<typename T>
void CppADS::ForwardList<T>::push_back(const T& value)
{
    std::unique_ptr<Node> back = std::make_unique<Node>(value, nullptr);
    m_tail->next = std::move(back);
    m_size++;
}

template<typename T>
void CppADS::ForwardList<T>::push_back(T&& value)
{
    std::unique_ptr<Node> back = std::make_unique<Node>(std::move(value), nullptr);
    m_tail->next = std::move(back);
    m_size++;
}

template<typename T>
void CppADS::ForwardList<T>::push_front(const T& value)
{
    std::unique_ptr<Node> front = std::make_unique<Node>(value, std::move(m_head));
    m_head = std::move(front);
    m_size++;
}

template<typename T>
void CppADS::ForwardList<T>::push_front(T&& value)
{
    std::unique_ptr<Node> front = std::make_unique<Node>(std::move(value), std::move(m_head));
    m_head = std::move(front);
    m_size++;
}

template<typename T>
void CppADS::ForwardList<T>::remove(iterator position_after)
{
    auto tmp = std::move(position_after.m_ptr->next->next);
    position_after.m_ptr->next = std::move(tmp);
    m_size--;

    if(position_after.m_ptr->next == nullptr)
        m_tail = position_after.m_ptr;
}

template<typename T>
void CppADS::ForwardList<T>:: remove_back()
{

}

template<typename T>
void CppADS::ForwardList<T>:: remove_front()
{
    std::unique_ptr<Node> front = std::move(m_head->next);
    m_head = std::move(front);
    m_size--;
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
T& CppADS::ForwardList<T>::operator[](size_t index)
{
    auto it = begin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
}

template<typename T>
const T& CppADS::ForwardList<T>::operator[](size_t index) const
{
    auto it = cbegin();
    for (int i = 0; i < index; i++)
    {
        it++;
    }
    return *it;
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

#endif //DOUBLEForwardList_H
