#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

#include <atomic>

namespace OSE {

    template<typename T>
    class Resource
    {
        static std::atomic<size_t> s_Counter;

        ResourceID m_RID;
    public:
        Resource() : m_RID{ ++s_Counter } { }
        virtual ~Resource() = default;

        virtual ResourceID GetRID() const
        {
            return m_RID;
        }
    };

    template<typename T>
    std::atomic<size_t> Resource<T>::s_Counter{ 0 };

}