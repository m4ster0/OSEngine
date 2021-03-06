#pragma once

#include "OSE/Math/Common.h"

#include <array>
#include <initializer_list>
#include <cassert>

namespace OSE {

    template<typename T, std::size_t n>
    struct Vector
    {
        std::array<T, n> components;

        Vector() = default;

        explicit Vector(const T& scalar)
        {
            for (T& elem : components)
                elem = scalar;
        }

        Vector(const std::initializer_list<T> args)
        {
            assert(args.size() <= n);

            int index = 0;
            for(auto it = args.begin(); it != args.end(); ++it, ++index)
                components[index] = *it;
        }

        T& operator[] (const std::size_t index)
        {
            assert(index >= 0 && index < n);
            return components[index];
        }

        const T& operator[] (const std::size_t index) const
        {
            assert(index >= 0 && index < n);
            return components[index];
        }

        template<typename = Math::FPEnabled<T>>
        inline T length()
        {
            T sum{ 0.0f };
            for (const T& comp : components)
                sum += comp * comp;
            return std::sqrt(sum);
        }

        template<typename = Math::FPEnabled<T>>
        inline void normalize()
        {
            T len = length();
            for (std::size_t i = 0; i < n; ++i)
                components[i] = components[i] / len;
        }
    };

    template<typename T>
    struct Vector<T, 2>
    {
        union
        {
            std::array<T, 2> components;

            struct
            {
                T x;
                T y;
            };
        };

        Vector() = default;

        explicit Vector(const T& scalar): x{ scalar }, y{ scalar }
        {

        }

        Vector(const std::initializer_list<T> args)
        {
            assert(args.size() <= 2);

            int index = 0;
            for(auto it = args.begin(); it != args.end(); ++it, ++index)
                components[index] = *it;
        }

        T& operator[] (const std::size_t index)
        {
            assert(index >= 0 && index < 2);
            return components[index];
        }

        const T& operator[] (const std::size_t index) const
        {
            assert(index >= 0 && index < 2);
            return components[index];
        }

        template<typename = Math::FPEnabled<T>>
        inline T length()
        {
            return std::sqrt(x * x + y * y);
        }

        template<typename = Math::FPEnabled<T>>
        inline void normalize()
        {
            T len = length();
            x /= len;
            y /= len;
        }
    };

    template<typename T>
    struct Vector<T, 3>
    {
        static Vector Zero;
        static Vector XAxis;
        static Vector YAxis;
        static Vector ZAxis;

        union
        {
            std::array<T, 3> components;

            struct
            {
                T x;
                T y;
                T z;
            };

            Vector<T, 2> xy;
        };

        Vector() = default;

        explicit Vector(const T& scalar): x{ scalar }, y{ scalar }, z{ scalar }
        {

        }

        Vector(const std::initializer_list<T> args)
        {
            assert(args.size() <= 3);

            int index = 0;
            for(auto it = args.begin(); it != args.end(); ++it, ++index)
                components[index] = *it;
        }

        Vector(const Vector<T, 2>& xy, const T& z): x{ xy.x }, y{ xy.y }, z{ z }
        {

        }

        T& operator[] (const std::size_t index)
        {
            assert(index >= 0 && index < 3);
            return components[index];
        }

        const T& operator[] (const std::size_t index) const
        {
            assert(index >= 0 && index < 3);
            return components[index];
        }

        template<typename = Math::FPEnabled<T>>
        inline T length()
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        template<typename = Math::FPEnabled<T>>
        inline void normalize()
        {
            T len = length();
            x /= len;
            y /= len;
            z /= len;
        }
    };

    template<typename T>
    struct Vector<T, 4>
    {
        union
        {
            std::array<T, 4> components;

            struct
            {
                T x;
                T y;
                T z;
                T w;
            };

            Vector<T, 2> xy;
            Vector<T, 3> xyz;
        };

        Vector() = default;

        explicit Vector(const T& scalar):
            x{ scalar }, y{ scalar }, z{ scalar }, w{ scalar }
        {

        }

        Vector(const std::initializer_list<T> args)
        {
            assert(args.size() <= 4);

            int index = 0;
            for(auto it = args.begin(); it != args.end(); ++it, ++index)
                components[index] = *it;
        }

        Vector(const Vector<T, 2>& xy, const T& z, const T& w):
            x{ xy.x }, y{ xy.y }, z{ z }, w{ w }
        {

        }

        Vector(const Vector<T, 3>& xyz, const T& w) :
                x{ xyz.x }, y{ xyz.y }, z{ xyz.z }, w{ w }
        {

        }

        T& operator[] (const std::size_t index)
        {
            assert(index >= 0 && index < 4);
            return components[index];
        }

        const T& operator[] (const std::size_t index) const
        {
            assert(index >= 0 && index < 4);
            return components[index];
        }

        template<typename = Math::FPEnabled<T>>
        inline T length()
        {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        template<typename = Math::FPEnabled<T>>
        inline void normalize()
        {
            T len = length();
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
    };

    using Vec2 = Vector<float, 2>;
    using Vec3 = Vector<float, 3>;
    using Vec4 = Vector<float, 4>;

    using IVec2 = Vector<int, 2>;
    using IVec3 = Vector<int, 3>;
    using IVec4 = Vector<int, 4>;

    template<typename T> Vector<T, 3> Vector<T, 3>::Zero{ 0, 0, 0 };
    template<typename T> Vector<T, 3> Vector<T, 3>::XAxis{ 1.0f, 0, 0 };
    template<typename T> Vector<T, 3> Vector<T, 3>::YAxis{ 0, 1.0f, 0 };
    template<typename T> Vector<T, 3> Vector<T, 3>::ZAxis{ 0, 0, 1.0f };

    // addition
    template<typename T, std::size_t n>
    Vector<T, n> operator+(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] + rhs[i];
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n> operator+(const Vector<T, n>& lhs, const T& scalar)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] + scalar;
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n> operator+(const T& scalar, const Vector<T, n>& rhs)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = scalar + rhs[i];
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator+=(Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        for (int i = 0; i < n; ++i)
            lhs[i] += rhs[i];
        return lhs;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator+=(Vector<T, n>& lhs, const T& scalar)
    {
        for (T& elem : lhs.components)
            elem += scalar;
        return lhs;
    }

    // subtraction
    template<typename T, std::size_t n>
    Vector<T, n> operator-(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] - rhs[i];
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n> operator-(const Vector<T, n>& lhs, const T& scalar)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] - scalar;
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator-=(Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        for (int i = 0; i < n; ++i)
            lhs[i] -= rhs[i];
        return lhs;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator-=(Vector<T, n>& lhs, const T& scalar)
    {
        for (T& elem : lhs.components)
            elem -= scalar;
        return lhs;
    }

    //multiplication
    template<typename T, std::size_t n>
    Vector<T, n> operator*(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] * rhs[i];
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n> operator*(const Vector<T, n>& lhs, const T& scalar)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] * scalar;
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n> operator*(const T& scalar, const Vector<T, n>& rhs)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = scalar * rhs[i];
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator*=(Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        for (int i = 0; i < n; ++i)
            lhs[i] *= rhs[i];
        return lhs;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator*=(Vector<T, n>& lhs, const T& scalar)
    {
        for (T& elem : lhs.components)
            elem *= scalar;
        return lhs;
    }

    // division
    template<typename T, std::size_t n>
    Vector<T, n> operator/(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] / rhs[i];
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n> operator/(const Vector<T, n>& lhs, const T& scalar)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = lhs[i] / scalar;
        return result;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator/=(Vector<T, n>& lhs, const Vector<T, n>& rhs)
    {
        for (int i = 0; i < n; ++i)
            lhs[i] /= rhs[i];
        return lhs;
    }

    template<typename T, std::size_t n>
    Vector<T, n>& operator/=(Vector<T, n>& lhs, const T& scalar)
    {
        for (T& elem : lhs.components)
            elem /= scalar;
        return lhs;
    }

    //two version for floating points and others
    //template<typename T, std::size_t n>
    //bool operator==(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
    //{
    //    for (int i = 0; i < n; ++i)
    //    {
    //        if (lhs[i] != rhs[i])
    //            return false;
    //    }

    //    return true;
    //}

    //template<typename T, std::size_t n>
    //bool operator!=(const Vector<T, n>& lhs, const Vector<T, n>& rhs)
    //{
    //    return !(lhs == rhs);
    //}

    template<typename T, std::size_t n>
    Vector<T, n> operator-(const Vector<T, n>& vec)
    {
        Vector<T, n> result;
        for (int i = 0; i < n; ++i)
            result[i] = -vec[i];

        return result;
    }

    namespace Math {

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        inline T distance(const Vector<T, n>& vec1, const Vector<T, n>& vec2)
        {
            return (vec1 - vec2).length();
        }

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        inline Vector<T, n> normalize(const Vector<T, n>& vec)
        {
            Vector<T, n> result{ vec };
            result.normalize();

            return result;
        }

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        inline T dot(const Vector<T, n>& vec1, const Vector<T, n>& vec2)
        {
            T result{};
            for (std::size_t i = 0; i < n; ++i)
                result += vec1[i] * vec2[i];

            return result;
        }

        template<typename T, typename = FPEnabled<T>>
        inline Vector<T, 3> cross(const Vector<T, 3>& vec1, const Vector<T, 3>& vec2)
        {
            Vector<T, 3> result;
            result.x = vec1.y * vec2.z - vec1.z * vec2.y;
            result.y = vec1.z * vec2.x - vec1.x * vec2.z;
            result.z = vec1.x * vec2.y - vec1.y * vec2.x;

            return result;
        }

    }
}