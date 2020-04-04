#ifndef HASH_FUNCTIONS_HPP
#define HASH_FUNCTIONS_HPP

#include <stdint.h>
#include <cstddef>
#include <cstring>
#include <type_traits>

namespace CppADS
{

template <typename T>
size_t hash(T key);

template <typename T>
typename std::enable_if<std::is_integral<T>::value, size_t>::type
hash(T key)
{
    return static_cast<size_t>(key);
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, size_t>
hash(T key)
{
    return hash(static_cast<typename std::underlying_type<T>::type>(key));
}

template <>
size_t hash(const char* key)
{
    size_t result = 0x0;
    for (auto i = 0; static_cast<size_t>(i) < strlen(key); i++)
        result ^= key[i] << (i % (sizeof(size_t) * 8));
    return result;
}

}

#endif
