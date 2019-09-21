
namespace ose {

    template<typename T, typename... Args>
    inline T* construct(memory::IMemoryResource& resource, Args&&... args)
    {
        return new (alignof(T), resource) T(std::forward<Args>(args)...);
    }

    template<typename T>
    inline T* construct_default(memory::IMemoryResource& resource)
    {
        return new (alignof(T), resource) T;
    }

    template<typename T, typename... Args>
    inline T* construct_array(memory::IMemoryResource& resource, std::size_t size, Args&&... args)
    {
        void* allocPtr = ::operator new(sizeof(T) * size, alignof(T), resource);
        if(allocPtr == nullptr)
            return nullptr;

        T* ptr = static_cast<T*>(allocPtr);
        for(std::size_t index = 0; index < size; ++index)
                new(static_cast<void*>(&ptr[index])) T(args...);

        return ptr;
    }

    template<typename T>
    inline T* construct_array_default(memory::IMemoryResource& resource, std::size_t size)
    {
        void* allocPtr = ::operator new(sizeof(T) * size, alignof(T), resource);
        if(allocPtr == nullptr)
            return nullptr;

        T* ptr = static_cast<T*>(allocPtr);
        for(std::size_t index = 0; index < size; ++index)
                new(static_cast<void*>(&ptr[index])) T;

        return ptr;
    }

    template<typename T>
    inline void destruct(T* ptr, memory::IMemoryResource& resource)
    {
        if(ptr != nullptr)
        {
            if constexpr(!std::is_trivially_destructible<T>::value)
            {
                ptr->~T();
            }

            void* allocPtr = static_cast<void*>(ptr);
            ::operator delete(allocPtr, alignof(T), resource);
        }
    }

    template<typename T>
    inline void destruct_array(T* ptr, std::size_t size, memory::IMemoryResource& resource)
    {
        if(ptr != nullptr)
        {
            if constexpr(!std::is_trivially_destructible<T>::value)
            {
                for(std::size_t index = 1; index <= size; ++index)
                    ptr[size - index]->~T();
            }

            void* allocPtr = static_cast<void*>(ptr);
            ::operator delete(allocPtr, alignof(T), resource);
        }
    }
}
