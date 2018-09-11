#pragma once

#include "OSE/TypeDefs.h"

#include <atomic>
#include <functional>

namespace OSE {

    enum class ResourceType: byte
    {
        None = 0,
        Swapchain,
        Program,
        VertexLayout,
        VertexBuffer,
        IndexBuffer,
        Texture
    };

    class ResourceID
    {
        size_t m_ID;
        ResourceType m_Type;

    public:
        static ResourceID Invalid;


        struct Hasher
        {
            std::size_t operator()(const ResourceID& rid) const
            {
                return std::hash<size_t>()(rid.m_ID);
            }
        };

        explicit ResourceID(size_t id, ResourceType type);
        ResourceID();

        bool operator==(const ResourceID& other) const;
        bool operator!=(const ResourceID& other) const;

        explicit operator bool() const
        {
            return static_cast<byte>(m_Type) > 0 && m_ID > 0;
        }
    };

    template<ResourceType type>
    struct RIDCounter
    {
        static std::atomic<size_t> Counter;
    };

    template<typename T>
    std::atomic<size_t> RIDCounter<T>::Counter{ 0 };

}