#pragma once

#include "OSE/Math/Common.h"
#include "OSE/Math/Vector.h"

namespace OSE {

    struct Quaternion
    {
        static Quaternion Identity;

        static Quaternion EulerAngles(float pitch, float yaw, float roll);
        static Quaternion AngleAxis(const Vec3& axis, float angleDegrees);
        static Quaternion LookRotation(const Vec3& forward, const Vec3& up);

        float w;
        union
        {
            Vec3 v;
            struct
            {
                float x;
                float y;
                float z;
            };
        };

        Quaternion() = default;
        Quaternion(float w, float x, float y, float z);
        Quaternion(float w, const Vec3& vec);
        explicit Quaternion(const Vec3& vec);

        inline float length() const
        {
            return std::sqrt(w * w + v.x * v.x + v.y * v.y + v.z * v.z);
        }

        inline void normalize()
        {
            float len = length();
            w /= len;
            v /= len;
        }

    };

    inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
    {
        float w = lhs.w*rhs.w - Math::dot(lhs.v, rhs.v);
        Vec3 v = lhs.w * rhs.v + rhs.w * lhs.v + Math::cross(lhs.v, rhs.v);

        return Quaternion{ w, v };
    }

    inline Vec3 operator*(const Quaternion& lhs, const Vec3& rhs)
    {
        //quat must be normalized
        return (2.0f * lhs.w * lhs.w - 1.0f) *rhs + 2.0f * Math::dot(lhs.v, rhs) * lhs.v + 2.0f * lhs.w * Math::cross(lhs.v, rhs);
    }

    namespace Math {

        inline Quaternion normalize(const Quaternion& quat)
        {
            Quaternion result{ quat };
            result.normalize();

            return result;
        }

        inline Quaternion conjugate(const Quaternion& quat)
        {
            return Quaternion{ quat.w, -quat.v };
        }

    }
}