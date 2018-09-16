#include "OSE/Graphics/ResourceStorage.h"

#include <algorithm>

namespace OSE {

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
    size_t ResourceStorage<R>::PutNext(R* resource)
    {
        size_t putIndex = m_NextIndex;
        resource->rid = putIndex;
        m_Storage[putIndex] = resource;

        do
            m_NextIndex++;
        while (m_NextIndex < m_Size && m_Storage[m_NextIndex] != nullptr);

        return putIndex;
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
        for (int i = 0; i < m_Size; ++i)
        {
            delete m_Storage[i];
            m_Storage[i] = nullptr;
        }

        m_NextIndex = 0;
    }

}