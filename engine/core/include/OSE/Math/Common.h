#pragma once

#include "OSE/Math/Vector.h"
#include "OSE/Math/Matrix.h"

#include <cmath>
#include <type_traits>

namespace OSE {
    namespace Math {

        /* constants */
        constexpr float pi = 3.1415926f;

        /* conversions */
        inline float toRadians(float degrees)
        {
            return degrees / 180.0f * pi;
        }

        inline double toRadians(double degrees)
        {
            return degrees / 180.0 * static_cast<double>(pi);
        }

        inline float toDegrees(float radians)
        {
            return radians / pi * 180.0f;
        }

        inline double toDegrees(double radians)
        {
            return radians / static_cast<double>(pi) * 180.0;
        }

        /* vector operations */
        template<typename FP>
        using FPEnabled = std::enable_if_t<std::is_floating_point<FP>::value>;

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        inline T length(const Vector<T, n>& vec)
        {
            T sum{};
            for (const T& comp : vec.components)
                sum += comp * comp;
            return std::sqrt(sum);
        }

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        inline T distance(const Vector<T, n>& vec1, const Vector<T, n>& vec2)
        {
            return length(vec1 - vec2);
        }

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        inline Vector<T, n> normalize(const Vector<T, n>& vec)
        {
            Vector<T, n> result;
            T len = length(vec);
            for (std::size_t i = 0; i < n; ++i)
                result[i] = vec[i] / len;

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

        /* ***************** */
        /* Matrix operations */
        /* ***************** */
        template<typename T, std::size_t m, std::size_t n>
        inline Matrix<T, n, m> transpose(const Matrix<T, m, n>& mat)
        {
            Matrix<T, n, m> result;

            for (std::size_t row = 0; row < m; ++row)
            {
                for (std::size_t col = 0; col < n; ++col)
                    result[n][m] = mat[m][n];
            }

            return result;
        }

        template<typename T, std::size_t n, typename = FPEnabled<T>>
        T determinant(const Matrix<T, n, n>& mat)
        {
            //gauss
            Matrix<T, n, n> tmp{ mat };
            T det{ 1.0 };
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