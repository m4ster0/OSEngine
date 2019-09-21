#pragma once

#include "ose/memory/i_memory_resource.h"
#include "ose/memory.h"

#include <memory>

namespace ose::stl {

    template<typename T>
    struct unique_ptr_deleter
    {
        explicit unique_ptr_deleter(ose::memory::IMemoryResource& resource):
            m_resource{ resource } {}

        void operator()(T* ptr) { ose::destruct(ptr, m_resource); }

    private:
        ose::memory::IMemoryResource& m_resource;
    }

    template<typename T>
    struct unique_ptr_deleter<T[]>
    {
        unique_ptr_deleter(ose::memory::IMemoryResource& resource, std::size_t size):
            m_resource{ resource }, m_size{ size } {}

        void operator()(T* ptr) { ose::destruct_array(ptr, m_size, m_resource); }

    private:
        ose::memory::IMemoryResource& m_resource;
        std::size_t m_size;
    }

    template<typename T, std::size_t N>
    struct unique_ptr_deleter<T[N]>; //Incomplete type for compile time arrays

    template<typename T>
    using unique_ptr = std::unique_ptr<T, unique_ptr_deleter<T>>;

    template<typename T>
    struct unique_if
    {
        using single_value = unique_ptr<T>;
    }

    template<typename T>
    struct unique_if<T[]>
    {
        using array_value_unknown_bounds = unique_ptr<T[]>;
    }

    template<typename T, std::size_t N>
    struct unique_if<T[N]>
    {
        using array_value_known_bounds = void;
    }

    template<typename T, typename... Args>
    typename unique_if<T>::single_value
    make_unique(ose::memory::IMemoryResource& resource, Args&&... args)
    {
        T* ptr = ose::construct<T>(resource, std::forward<Args>(args)...);
        return unique_ptr<T>(ptr, unique_ptr_deleter<T>(resource));
    }

    template<typename T>
    typename unique_if<T>::single_value
    make_unique_default(ose::memory::IMemoryResource& resource)
    {
        T* ptr = ose::construct_default<T>(resource);
        return unique_ptr<T>(ptr, unique_ptr_deleter<T>(resource));
    }

    template<typename T, typename... Args>
    typename unique_if<T>::array_value_unknown_bounds
    make_unique(ose::memory::IMemoryResource& resource, std::size_t size, Args&&... args)
    {
        using Type = std::remove_extent<T>::type;

        Type* ptr = ose::construct_array<Type>(resource, size, std::forward<Args>(args)...);
        return unique_ptr<T>(ptr, unique_ptr_deleter<T>(resource, size));
    }

    template<typename T>
    typename unique_if<T>::array_value_unknown_bounds
    make_unique_default(ose::memory::IMemoryResource& resource, std::size_t size)
    {
        using Type = std::remove_extent<T>::type;

        Type* ptr = ose::construct_array_default<Type>(resource, size);
        return unique_ptr<T>(ptr, unique_ptr_deleter<T>(resource, size));
    }

    template<typename T, typename... Args>
    typename unique_if<T>::array_value_unknown_bounds
    make_unique(ose::memory::IMemoryResource& resource, Args&&... args) = delete;

    template<typename T, typename... Args>
    typename unique_if<T>::array_value_known_bounds
    make_unique(ose::memory::IMemoryResource& resource, Args&&... args) = delete;

    template<typename T>
    typename unique_if<T>::array_value_unknown_bounds
    make_unique_default(ose::memory::IMemoryResource& resource) = delete;

    template<typename T>
    typename unique_if<T>::array_value_known_bounds
    make_unique_default(ose::memory::IMemoryResource& resource) = delete;

    template<typename T, typename... Args>
    typename unique_if<T>::single_value
    make_unique(ose::memory::IMemoryResource& resource, std::size_t size, Args&&... args) = delete;

    template<typename T, typename... Args>
    typename unique_if<T>::array_value_known_bounds
    make_unique(ose::memory::IMemoryResource& resource, std::size_t size, Args&&... args) = delete;

    template<typename T>
    typename unique_if<T>::single_value
    make_unique_default(ose::memory::IMemoryResource& resource, std::size_t size) = delete;

    template<typename T>
    typename unique_if<T>::array_value_known_bounds
    make_unique_default(ose::memory::IMemoryResource& resource, std::size_t size) = delete;
}
