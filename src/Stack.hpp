#ifndef STACK_H
#define STACK_H

#include "Container.hpp"

#include <memory>

namespace CppADS
{
    template<class T>
    /// @brief Stack (LIFO) class
    class Stack : public IContainer
    {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        Stack() = default;                          ///< Default constructor
        Stack(const Stack<T>& copy);                ///< Copy contructor
        Stack(Stack<T>&& move);                     ///< Move contructor
        Stack(std::initializer_list<T> init_list);  ///< Contructor from initializer list

        Stack<T>& operator=(const Stack<T>& copy);  ///< Copy assignment operator
        Stack<T>& operator=(Stack<T>&& move);       ///< Move assignment operator

        ~Stack() = default;                         ///< Destructor

        /// @brief Remove all data from container
        void clear() override;

        /// @brief Get size of container
        /// @return element's count
        size_t size() const override;

        /// @brief Push value on top of the stack
        /// @param value added value
        void push(const T& value);

        /// @brief Overloaded method
        void push(T&& value);

        /// @brief Get last inserted value
        /// @return value on top of the stack
        T& top();

        /// @brief Overloaded method
        const T& top() const;

        /// @brief Remove top item
        void  pop();

    private:

        struct Node
        {
            T Value;
            std::unique_ptr<Node> Next { nullptr };
            Node(T _value, std::unique_ptr<Node>&& _next = nullptr)
                : Value(_value), Next(std::move(_next)) {}
        };

        std::unique_ptr<Node> m_head { nullptr };   ///< Pointer to the top of the stack
        size_t m_size { 0 };                        ///< Stack size
    };
}

template<class T>
CppADS::Stack<T>::Stack(const Stack<T>& copy)
{
    m_size = copy.m_size;

    std::unique_ptr<Node>* self_node = &m_head;
    const std::unique_ptr<Node>* copy_node = &(copy.m_head);

    while ((*copy_node) != nullptr)
    {
        *self_node = std::make_unique<Node>(copy_node->get()->Value);

        self_node = &(self_node->get()->Next);
        copy_node = &(copy_node->get()->Next);
    }
}

template<class T>
CppADS::Stack<T>::Stack(Stack<T>&& move)
{
    m_head = std::move(move.m_head);
    m_size = std::move(move.m_size);
    move.m_size = 0;
}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(const Stack<T>& copy)
{
    m_head.reset(nullptr);
    m_size = copy.m_size;

    std::unique_ptr<Node>* self_node = &m_head;
    const std::unique_ptr<Node>* copy_node = &(copy.m_head);

    while ((*copy_node) != nullptr)
    {
        *self_node = std::make_unique<Node>(copy_node->get()->Value);

        self_node = &(self_node->get()->Next);
        copy_node = &(copy_node->get()->Next);
    }
    return *this;
}

template<class T>
CppADS::Stack<T>& CppADS::Stack<T>::operator=(Stack<T>&& move)
{
    m_head = std::move(move.m_head);
    m_size = std::move(move.m_size);
    move.m_size = 0;
    return *this;
}

template<class T>
CppADS::Stack<T>::Stack(std::initializer_list<T> init_list)
{
    for (auto it = init_list.begin(); it != init_list.end(); it++)
    {
        push(*it);
    }
}

template<class T>
void CppADS::Stack<T>::clear()
{
    m_head.reset(nullptr);
    m_size = 0;
}

template<class T>
size_t CppADS::Stack<T>::size() const
{
    return m_size;
}

template<class T>
void CppADS::Stack<T>::push(const T& value)
{
    m_size++;
    std::unique_ptr<Node> new_top = std::make_unique<Node>(value, std::move(m_head));
    m_head = std::move(new_top);
}

template<class T>
void CppADS::Stack<T>::push(T&& value)
{
    m_size++;
    std::unique_ptr<Node> new_top = std::make_unique<Node>(std::move(value), std::move(m_head));
    m_head = std::move(new_top);
}

template<class T>
T& CppADS::Stack<T>::top()
{
    if (m_head != nullptr)
    {
        return m_head->Value;
    }
    else
    {
        throw std::out_of_range("CppADS::Stack<T>::top: stack is empty");
    }
}

template<class T>
const T& CppADS::Stack<T>::top() const
{
    if (m_head != nullptr)
    {
        return m_head->Value;
    }
    else
    {
        throw std::out_of_range("CppADS::Stack<T>::top: stack is empty");
    }
}

template<class T>
void CppADS::Stack<T>::pop()
{
    m_size--;
    m_head = std::move(m_head->Next);
}
#endif //STACK_H
