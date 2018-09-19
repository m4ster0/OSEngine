#pragma once

#include "OSE/Math/Vector.h"
#include "OSE/Math/Matrix.h"

#include <cmath>

namespace OSE {

    template<typename T>
    using FPType = typename std::enable_if<std::is_floating_point<T>::value, T>::type;

    template<typename T, std::size_t n>
    inline FPType<T> length(const Vector<T, n>& vec)
    {
        T sum{};
        for (const T& comp : vec.components)
            sum += comp * comp;
        return std::sqrt(sum);
    }

    template<typename T, std::size_t n>
    inline FPType<T> distance(const Vector<T, n>& vec1, const Vector<T, n>& vec2)
    {
        return length(vec1 - vec2);
    }

    template<typename T, std::size_t n, FPType<T>>
    inline Vector<T, n> normalize(const Vector<T, n>& vec)
    {
        Vector<T, n> result;
        T len = length(vec);
        for (std::size_t i = 0; i < n; ++i)
            result[i] = vec[i] / len;

        return result;
    }

    template<typename T, std::size_t n, FPType<T>>
    inline FPType<T> dot(const Vector<T, n>& vec1, const Vector<T, n>& vec2)
    {
        T result{};
        for (std::size_t i = 0; i < n; ++i)
            result[i] += vec1[i] * vec2[i];

        return result;
    }

    template<typename T, FPType<T>>
    inline Vector<T, 3> cross(const Vector<T, 3>& vec1, const Vector<T, 3>& vec2)
    {
        Vector<T, 3> result;
        result.x = vec1.y * vec2.z - vec1.z * vec2.y;
        result.y = vec1.z * vec2.x - vec1.x * vec2.z;
        result.z = vec1.x * vec2.y - vec1.y * vec2.x;

        return result;
    }

    /* ***************** */
    /* Matrix operations */
    /* ***************** */
    template<typename T, std::size_t m, std::size_t n>
    Matrix<T, n, m> transpose(const Matrix<T, m, n>& mat)
    {
        Matrix<T, n, m> result;

        for (std::size_t row = 0; row < m; ++row)
        {
            for (std::size_t col = 0; col < n; ++col)
                result[n][m] = mat[m][n];
        }

        return result;
    }

    template<typename T, std::size_t n>
    inline FPType<T> determinant(const Matrix<T, n, n>& mat)
    {
        //gauss
        Matrix<T, n, n> tmp{ mat };
        T det{ 1.0f };
        for (std::size_t i = 0; i < n; ++i)
        {
            det *= tmp[i][i];
            for (std::size_t j = i + 1; j < n; ++j)
            {
                T colRatio = tmp[i][j] / tmp[i][i];
                for (std::size_t k = i + 1; k < n; ++k)
                    tmp[k][j] -= colRatio * tmp[k][i];
            }
        }

        return det;
    }

    template<typename T, std::size_t n, FPType<T>>
    inline bool inverse(Matrix<T, n, n>& mat)
    {
        T det = determinant(mat);
        if (det != 0)
        {
            //TODO
            return true;
        }

        return false;
    }

}