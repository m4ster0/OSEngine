#pragma once

#include "OSE/Graphics/GLResource.h"

#include <OSE/TypeDefs.h>

#include <memory>
#include <vector>
#include <utility>

namespace OSE {

    template<class R> //in concepts constrain R to be derived of GLResource
    class ResourceStorage
    {
        std::unique_ptr<R*[]> m_Storage;
        size_t m_Size;
        size_t m_NextIndex{ 0 };

    public:
        ResourceStorage(size_t maxSize);

        ResourceStorage(ResourceStorage&&) = delete;
        ResourceStorage& operator=(ResourceStorage&&) = delete;

        ~ResourceStorage();

        R* At(size_t index) const;
        void Remove(size_t index);

        template<typename... Args>
        R& CreateNext(Args&& ...args);

        bool HasNext() const;

        void Clear();
    };

    template<class R>
    ResourceStorage<R>::ResourceStorage(size_t maxSize):
        m_Size{ maxSize }, m_Storage{ nullptr }
    {
        m_Storage = std::unique_ptr<R*[]>(new R*[maxSize] {});
    }

    template<class R>
    ResourceStorage<R>::~ResourceStorage()
    {
        Clear();
    }

    template<class R>
    bool ResourceStorage<R>::HasNext() const
    {
        return m_NextIndex < m_Size;
    }

    template<class R>
    template<typename... Args>
    R& ResourceStorage<R>::CreateNext(Args&& ...args)
    {
        R* resource = new R(m_NextIndex, std::forward<Args>(args)...);
        m_Storage[m_NextIndex] = resource;

        do
            m_NextIndex++;
        while (m_NextIndex < m_Size && m_Storage[m_NextIndex] != nullptr);

        return *resource;
    }

    template<class R>
    R* ResourceStorage<R>::At(size_t index) const
    {
        if (index < m_Size)
            return m_Storage[index];

        return nullptr;
    }

    template<class R>
    void ResourceStorage<R>::Remove(size_t index)
    {
        if (index < m_Size)
        {
            delete m_Storage[index];
            m_Storage[index] = nullptr;

            if (index < m_NextIndex)
                m_NextIndex = index;
        }
    }

    template<class R>
    void ResourceStorage<R>::Clear()
    {
        for (uint i = 0; i < m_Size; ++i)
        {
            delete m_Storage[i];
            m_Storage[i] = nullptr;
        }

        m_NextIndex = 0;
    }
}