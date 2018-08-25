#pragma once

#include "OSE/TypeDefs.h"

#include <functional>

namespace OSE {

    class ResourceID
    {
        size_t m_ID;

    public:
        static ResourceID Invalid;

        struct Hasher
        {
            std::size_t operator()(const ResourceID& rid) const
            {
                return std::hash<size_t>()(rid.m_ID);
            }
        };

        explicit ResourceID(size_t id);
        ResourceID();

        bool operator==(const ResourceID& other) const;
        bool operator!=(const ResourceID& other) const;

        explicit operator bool() const
        {
            return m_ID > 0;
        }
    };

}