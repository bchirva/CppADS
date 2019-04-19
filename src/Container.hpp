#pragma once

#include <stddef.h>

namespace CppADS
{
    class IContainer
    {
    public:
        virtual void clear() = 0;
        virtual size_t size() const = 0;
    };
}
