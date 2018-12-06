#pragma once

#include "OSE/Math/Common.h"
#include "OSE/Math/Vector.h"

#include <array>
#include <initializer_list>
#include <cassert>

namespace OSE {

    /*
        m x n dimension template matrix. Stored in row-major order.
    */

    template<typename T, std::size_t m, std::size_t n>
    struct Matrix
    {
        union
        {
            std::array<T, m * n> elements;
            Vector<T, n> rows[m];
        };

        Matrix(): elements{}
        {
            std::size_t index = 0;
            while (index < m * n)
            {
                elements[index] = 1;
                index += m + 1;
            }
        }

        Matrix(const std::initializer_list<T> args)
        {
            assert(args.size() <= m * n);

            std::size_t index = 0;
            for (auto it = args.begin(); it != args.end(); ++it, ++index)
            {
                elements[index] = *it;
            }
        }

        Vector<T, n>& operator[](const std::size_t index)
        {
            assert(index >= 0 && index < m);
            return rows[index];
        }

        const Vector<T, n>& operator[](const std::size_t index) const
        {
            assert(index >= 0 && index < m);
            return rows[index];
        }
    };

    using Mat2 = Matrix<float, 2, 2>;
    using Mat3 = Matrix<float, 3, 3>;
    using Mat4 = Matrix<float, 4, 4>;


    template<typename T, std::size_t m, std::size_t n>
    Matrix<T, m, n> operator+(const Matrix<T, m, n>& lhs, const Matrix<T, m, n>& rhs)
    {
        Matrix<T, m, n> result;
        for (std::size_t i = 0; i < m * n; ++i)
        {
            result.elements[i] = lhs.elements[i] + rhs.elements[i];
        }

        return result;
    }

    template<typename T, std::size_t m, std::size_t n>
    Matrix<T, m, n> operator-(const Matrix<T, m, n>& lhs, const Matrix<T, m, n>& rhs)
    {
        Matrix<T, m, n> result;
        for (std::size_t i = 0; i < m * n; ++i)
        {
            result.elements[i] = lhs.elements[i] - rhs.elements[i];
        }

        return result;
    }

    template<typename T, std::size_t m, std::size_t n, std::size_t k>
    Matrix<T, m, k> operator*(const Matrix<T, m, n>& lhs, const Matrix<T, n, k>& rhs)
    {
        Matrix<T, m, k> result;
        for (std::size_t i = 0; i < m * k; ++i)
        {
            std::size_t row = i / k;
            std::size_t col = i % k;

            result[row][col] = T{};
            for (std::size_t j = 0; j < n; ++j)
                result[row][col] += lhs[row][j] * rhs[j][col];
        }

        return result;
    }

    template<typename T, std::size_t n, std::size_t k>
    Vector<T, k> operator*(const Vector<T, n>& lhs, const Matrix<T, n, k>& rhs)
    {
        Vector<T, k> result;
        for (std::size_t col = 0; col < k; ++col)
        {
            result[col] = T{};
            for (std::size_t j = 0; j < n; ++j)
                result[col] += lhs[j] * rhs[j][col];
        }

        return result;
    }

    namespace Math {

        template<typename T, std::size_t m, std::size_t n>
        inline Matrix<T, n, m> transpose(const Matrix<T, m, n>& mat)
        {
            Matrix<T, n, m> result;

            for (std::size_t row = 0; row < m; ++row)
            {
                for (std::size_t col = 0; col < n; ++col)
                    result[col][row] = mat[row][col];
            }

            return result;
        }

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        T determinant(const Matrix<T, n, n>& mat)
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

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        bool inverse(Matrix<T, n, n>& mat)
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
}