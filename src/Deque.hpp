#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "Container.hpp"

#include <memory>

namespace CppADS
{
    template<typename T>
    /// @brief Double-endian queue class
    class Deque : public IContainer
    {
    public:
        Deque() = default;                          ///< Default constructor
        Deque(const Deque<T>& copy);                ///< Copy constructor
        Deque(Deque<T>&& move);                     ///< Move constructor
        Deque(std::initializer_list<T> init_list);  ///< Contructor from initializer list

        Deque<T>& operator=(const Deque<T>& copy);  ///< Copy assignment operator
        Deque<T>& operator=(Deque<T>&& move);       ///< Move assignment operator

        ~Deque() = default;                         ///< Destructor

        /// @brief Remove all data from container
        void clear() override;
        
        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Insert element to the end
        /// @param value inserted item
        void push_back(const T& value);
        
        /// @brief Overloaded method
        void push_back(T&& value);
        
        /// @brief Insert element to the beginning
        /// @param value
        void push_front(const T& value);
        
        /// @brief Overloaded method
        void push_front(T&& value);

        /// @brief Remove last element
        void pop_back();
        
        /// @brief Remove first element
        void pop_front();

        /// @brief Access to the first element
        /// @return Reference to the first element 
        T& front();
        
        /// @brief Access to the first element
        /// @return Reference to the first element 
        const T& front() const;

        /// @brief Access to the last element
        /// @return Reference to the last element 
        T& back();
        
        /// @brief Access to the last element
        /// @return Reference to the last element 
        const T& back() const;

    private:
        struct Node
        {
            T Value;
            std::shared_ptr<Node> Next { nullptr };
            std::shared_ptr<Node> Prev { nullptr };
            Node (T _value, std::shared_ptr<Node> _next, std::shared_ptr<Node> _prev)
                : Value(_value), Next(_next), Prev(_prev) {}
        };

        std::shared_ptr<Node> m_front { nullptr };      ///< Pointer to the front item
        std::shared_ptr<Node> m_back { nullptr };       ///< Pointer to the back item
        size_t m_size { 0 };                            ///< Container size
    };
}

template<typename T>
CppADS::Deque<T>::Deque(const Deque<T>& copy)
{
    std::shared_ptr<Node> src = copy.m_front;
    while(src != nullptr)
    {
        push_back(src->Value);
        src = src->Next;
    }
}

template<typename T>
CppADS::Deque<T>::Deque(Deque<T>&& move)
{
    m_size = std::move(move.m_size);
    m_front = std::move(move.m_front);
    m_back = std::move(move.m_back);
    move.m_size = 0;
}

template<typename T>
CppADS::Deque<T>::Deque(std::initializer_list<T> init_list)
{
    for (auto it = init_list.begin(); it != init_list.end(); ++it)
    {
        push_back(*it);
    }
}

template<typename T>
CppADS::Deque<T>& CppADS::Deque<T>::operator=(const Deque<T>& copy)
{
    clear();
    std::shared_ptr<Node> src = copy.m_front;
    while(src != nullptr)
    {
        push_back(src->Value);
        src = src->Next;
    }
    return *this;
}

template<typename T>
CppADS::Deque<T>& CppADS::Deque<T>::operator=(Deque<T>&& move)
{
    clear();
    m_size = std::move(move.m_size);
    m_front = std::move(move.m_front);
    m_back = std::move(move.m_back);
    move.m_size = 0;
    return *this;
}

template<typename T>
void CppADS::Deque<T>::push_back(const T& value)
{
    if (m_size != 0)
    {    
        std::shared_ptr<Node> new_item = std::make_shared<Node>(value, nullptr, m_back->Prev);
        m_back->Next = new_item;
        m_back = new_item;
    }
    else
    {
        m_back = m_front = std::make_shared<Node>(value, nullptr, nullptr);
    }
    m_size++;
}

template<typename T>
void CppADS::Deque<T>::push_back(T&& value)
{
    if (m_size != 0)
    {    
        std::shared_ptr<Node> new_item = std::make_shared<Node>(std::move(value), nullptr, m_back->Prev);
        m_back->Next = new_item;
        m_back = new_item;
    }
    else
    {
        m_back = m_front = std::make_shared<Node>(std::move(value), nullptr, nullptr);
    }
    m_size++;
}

template<typename T>
void CppADS::Deque<T>::push_front(const T& value)
{
    if (m_size != 0)
    {
        std::shared_ptr<Node> new_item = std::make_shared<Node>(value, m_front->Next, nullptr);
        m_front->Prev = new_item;
        m_front = new_item;
    }
    else
    {
        m_back = m_front = std::make_shared<Node>(value, nullptr, nullptr);
    }
    m_size++;
}

template<typename T>
void CppADS::Deque<T>::push_front(T&& value)
{
    if (m_size != 0)
    {
        std::shared_ptr<Node> new_item = std::make_shared<Node>(std::move(value), m_front->Next, nullptr);
        m_front->Prev = new_item;
        m_front = new_item;
    }
    else
    {
        m_back = m_front = std::make_shared<Node>(std::move(value), nullptr, nullptr);
    }
    m_size++;
}

template<typename T>
void CppADS::Deque<T>::pop_back()
{
    if(m_back != nullptr)
    {
        m_back = m_back->Prev;
        if (m_back == nullptr)
        {
            m_front = nullptr;        
        }
        else
        {
            m_back->Next = nullptr;
        }
        m_size--;
    }
}

template<typename T>
void CppADS::Deque<T>::pop_front()
{
    if(m_front != nullptr)
    {
        m_front = m_front->Next;
        if (m_front == nullptr)
        {
            m_back = nullptr;        
        }
        else
        {
            m_front->Prev = nullptr;
        }
        m_size--;
    }
}

template<typename T>
T& CppADS::Deque<T>::front()
{
    if(m_front != nullptr)
    {
        return m_front->Value;
    }
    else
    {
        throw std::out_of_range("CppADS::Deque<T>::front: deque is empty");
    }
}

template<typename T>
const T& CppADS::Deque<T>::front() const
{
    if(m_front != nullptr)
    {
        return m_front->Value;
    }
    else
    {
        throw std::out_of_range("CppADS::Deque<T>::front: deque is empty");
    }
}

template<typename T>
T& CppADS::Deque<T>::back()
{
    if(m_back != nullptr)
    {
        return m_back->Value;
    }
    else
    {
        throw std::out_of_range("CppADS::Deque<T>::back: deque is empty");
    }
}

template<typename T>
const T& CppADS::Deque<T>::back() const
{
    if(m_back != nullptr)
    {
        return m_back->Value;
    }
    else
    {
        throw std::out_of_range("CppADS::Deque<T>::back: deque is empty");
    }
}

template<typename T>
size_t CppADS::Deque<T>::size() const
{
    return m_size;
}

template<typename T>
void CppADS::Deque<T>::clear()
{
    while(m_front != nullptr)
        pop_front();
}

#endif
