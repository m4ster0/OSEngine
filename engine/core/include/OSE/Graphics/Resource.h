#pragma once

#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

namespace OSE {

    class Resource
    {
        ResourceID m_RID{ };
    public:
        Resource() = default;

        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;

        Resource(Resource&&) = delete;
        Resource& operator=(Resource&&) = delete;

        virtual ~Resource() = default;

        ResourceID GetRID() const
        {
            return m_RID;
        }

        virtual void Dispose() = 0;
    };

}