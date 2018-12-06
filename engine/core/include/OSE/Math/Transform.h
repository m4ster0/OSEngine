#pragma once

#include "OSE/Math/Common.h"
#include "OSE/Math/Vector.h"
#include "OSE/Math/Matrix.h"
#include "OSE/Math/Quaternion.h"

namespace OSE { namespace Math {

        //scale
        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> scale(const Vector<T, 3>& scale)
        {
            Matrix<T, 4, 4> result;
            for (int i = 0; i < 3; ++i)
                result[i][i] = scale[i];

            return result;
        }

        //shear
        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> shear(const Vector<T, 3>& shearX, const Vector<T, 3>& shearY, const Vector<T, 3>& shearZ)
        {
            Matrix<T, 4, 4> result;
            result[1][0] = shearX.y;
            result[2][0] = shearX.z;

            result[0][1] = shearY.x;
            result[2][1] = shearY.z;

            result[0][2] = shearZ.x;
            result[1][2] = shearZ.y;

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

        //rotation roll -> yaw -> pitch
        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> rotate(T pitch, T yaw, T roll)
        {
            Matrix<T, 4, 4> result;

            T xRadians = Math::toRadians(pitch);
            T yRadians = Math::toRadians(yaw);
            T zRadians = Math::toRadians(roll);
            T cx = std::cos(xRadians), sx = std::sin(xRadians);
            T cy = std::cos(yRadians), sy = std::sin(yRadians);
            T cz = std::cos(zRadians), sz = std::sin(zRadians);

            result[0][0] = cy*cz;
            result[0][1] = sx*sy*cz + cx*sz;
            result[0][2] = -cx*sy*cz + sx*sz;

            result[1][0] = -cy*sz;
            result[1][1] = -sx*sy*sz + cx*cz;
            result[1][2] = cx*sy*sz + sx*cz;

            result[2][0] = sy;
            result[2][1] = -sx*cy;
            result[2][2] = cx*cy;

            return result;
        }

        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> rotate(T angleDegrees, const Vector<T, 3>& axisVec)
        {
            Vector<T, 3> axis = normalize(axisVec);
            Matrix<T, 4, 4> result;

            float angleRadians = toRadians(angleDegrees);
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

        inline Mat4 rotate(const Quaternion& quat)
        {
            Quaternion rot = normalize(quat);
            Mat4 result;

            result[0][0] = 1.0f - 2.0f*rot.v.y*rot.v.y - 2.0f*rot.v.z*rot.v.z;
            result[0][1] = 2.0f*rot.v.x*rot.v.y + 2.0f*rot.w*rot.v.z;
            result[0][2] = 2.0f*rot.v.x*rot.v.z - 2.0f*rot.w*rot.v.y;

            result[1][0] = 2.0f*rot.v.x*rot.v.y - 2.0f*rot.w*rot.v.z;
            result[1][1] = 1.0f - 2.0f*rot.v.x*rot.v.x - 2.0f*rot.v.z*rot.v.z;
            result[1][2] = 2.0f*rot.v.y*rot.v.z + 2.0f*rot.w*rot.v.x;

            result[2][0] = 2.0f*rot.v.x*rot.v.z + 2.0f*rot.w*rot.v.y;
            result[2][1] = 2.0f*rot.v.y*rot.v.z - 2.0f*rot.w*rot.v.x;
            result[2][2] = 1.0f - 2.0f*rot.v.x*rot.v.x - 2.0f*rot.v.y*rot.v.y;

            return result;
        }

        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> lookAt(const Vector<T, 3>& eye, const Vector<T, 3>& at, const Vector<T, 3>& up)
        {
            Matrix<T, 4, 4> result;

            Vector<T, 3> zAxis = normalize(at - eye);
            Vector<T, 3> xAxis = normalize(cross(up, zAxis));
            Vector<T, 3> yAxis = cross(zAxis, xAxis);

            result[0].xyz = Vector<T, 3>{ xAxis.x, yAxis.x, -zAxis.x };
            result[1].xyz = Vector<T, 3>{ xAxis.y, yAxis.y, -zAxis.y };
            result[2].xyz = Vector<T, 3>{ xAxis.z, yAxis.z, -zAxis.z };
            result[3].xyz = Vector<T, 3>{ dot(xAxis, -eye), dot(yAxis, -eye), -dot(zAxis, -eye) };

            return result;
        }

        inline Mat4 lookAt(const Vec3& position, const Quaternion& direction)
        {
            Mat4 result;

            Vec3 zAxis = direction * Vec3::ZAxis;
            Vec3 xAxis = direction * Vec3::XAxis;
            Vec3 yAxis = direction * Vec3::YAxis;

            result[0].xyz = Vec3{ xAxis.x, yAxis.x, -zAxis.x };
            result[1].xyz = Vec3{ xAxis.y, yAxis.y, -zAxis.y };
            result[2].xyz = Vec3{ xAxis.z, yAxis.z, -zAxis.z };
            result[3].xyz = Vec3{ dot(xAxis, -position), dot(yAxis, -position), -dot(zAxis, -position) };

            return result;
        }

        template<typename T, typename = FPEnabled<T>>
        inline Matrix<T, 4, 4> orthographic(T left, T right, T bottom, T top, T near, T far)
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
        inline Matrix<T, 4, 4> perspective(T fovDegrees, T aspectRatio, T near, T far)
        {
            Matrix<T, 4, 4> result;

            float fovRadians = toRadians(fovDegrees);
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