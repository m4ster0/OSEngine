#pragma once

#include "OSE/TypeDefs.h"

#include <atomic>
#include <functional>

namespace OSE {

    enum class ResourceType: byte
    {
        Program,
        VertexLayout,
        Buffer,
        Texture
    };

    template<ResourceType RT>
    class ResourceID
    {
        int32 m_ID;

    public:
        static ResourceID Invalid;

        struct Hasher
        {
            std::size_t operator()(const ResourceID<RT>& rid) const
            {
                return std::hash<size_t>()(rid.m_ID);
            }
        };

        ResourceID(int32 id) : m_ID{ id } { }
        ResourceID(): ResourceID(-1) { }

        inline int32 GetID() const { return m_ID; }

        bool operator==(const ResourceID<RT>& other) const
        {
            return m_ID == other.m_ID;
        }

        bool operator!=(const ResourceID<RT>& other) const
        {
            return !(*this == other);
        }

        explicit operator bool() const
        {
            return m_ID >= 0;
        }
    };

    using SwapChainHandle = size_t;
    using ProgramHandle = ResourceID<ResourceType::Program>;
    using VertexLayoutHandle = ResourceID<ResourceType::VertexLayout>;
    using BufferHandle = ResourceID<ResourceType::Buffer>;
    using TextureHandle = ResourceID<ResourceType::Texture>;

    template<ResourceType RT>
    ResourceID<RT> ResourceID<RT>::Invalid;
}