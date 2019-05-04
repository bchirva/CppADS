#pragma once

#include <stddef.h>

namespace CppADS
{
    /// @brief Base class for all containers
    class IContainer
    {
    public:

        /// @brief Remove all data from container
        virtual void clear() = 0;

        /// @brief Get size of container 
        /// @return Count of items 
        virtual size_t size() const = 0;
    };
}
