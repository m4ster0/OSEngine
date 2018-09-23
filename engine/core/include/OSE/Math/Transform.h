#pragma once

#include "OSE/Math/Vector.h"
#include "OSE/Math/Matrix.h"

#include <cmath>
#include <type_traits>

namespace OSE { namespace Math {

        template<typename FP>
        using FPEnabled = std::enable_if_t<std::is_floating_point<FP>::value>;

        //scale
        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> scale(const Vector<T, 3>& scale)
        {
            Matrix<T, 4, 4> result;
            for (int i = 0; i < 3; ++i)
                result[i][i] = scale[i];

            return result;
        }

        //translate
        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> translate(const Vector<T, 3>& translation)
        {
            Matrix<T, 4, 4> result;
            result[3].xyz = translation;

            return result;
        }

        //rotate
        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> rotate(const T angleRadians, const Vector<T, 3>& axisVec)
        {
            Vec3 axis = normalize(axisVec);
            Matrix<T, 4, 4> result;

            const float c = std::cos(angleRadians);
            const float s = std::sin(angleRadians);
            const float t = 1.0f - c;

            result[0][0] = t*axis.x*axis.x + c;
            result[0][1] = t*axis.x*axis.y + s*axis.z;
            result[0][2] = t*axis.x*axis.z - s*axis.y;

            result[1][0] = t*axis.x*axis.y - s*axis.z;
            result[1][1] = t*axis.y*axis.y + c;
            result[1][2] = t*axis.y*axis.z + s*axis.x;

            result[2][0] = t*axis.x*axis.z + s*axis.y;
            result[2][1] = t*axis.y*axis.z - s*axis.x;
            result[2][2] = t*axis.z*axis.z + c;

            return result;
        }

        template<typename T, typename = FPEnabled<T>>
        Matrix<T, 4, 4> orthographic(T left, T right, T top, T bottom, T near, T far)
        {
            Matrix<T, 4, 4> result;
            result[0][0] = 2.0f / (right - left);
            result[3][0] = -(right + left) / (right - left);

            result[1][1] = 2.0f / (top - bottom);
            result[3][1] = -(top + bottom) / (top - bottom);

            result[2][2] = -2.0f / (far - near);
            result[3][2] = -(far + near) / (far - near);

            result[3][3] = 1.0f;
            return result;
        }

        template<typename T, typename = FPEnabled<T>>
        Matrix<T, 4, 4> perspective(T fovRadians, T aspectRatio, T near, T far)
        {
            Matrix<T, 4, 4> result;

            T top = near * std::tan(fovRadians / 2.0f);
            T right = top * aspectRatio;

            result[0][0] = near / right;
            result[1][1] = near / top;
            result[2][2] = -(far + near) / (far - near);
            result[3][2] = -2.0f * far * near / (far - near);
            result[2][3] = -1.0f;
            result[3][3] = 0;

            return result;
        }

} }