#include "OSE/Math/Quaternion.h"

#include <limits>
#include <cmath>
#include <cassert>

namespace OSE {

    Quaternion Quaternion::Identity{ 0, Vec3::Zero };

    Quaternion Quaternion::EulerAngles(float pitch, float yaw, float roll)
    {
        Quaternion pitchQ = Quaternion::AngleAxis(Vec3{ 1.0f, 0, 0 }, pitch);
        Quaternion yawQ = Quaternion::AngleAxis(Vec3{ 0, 1.0f, 0 }, yaw);
        Quaternion rollQ = Quaternion::AngleAxis(Vec3{ 0, 0, 1.0f }, roll);

        return rollQ * yawQ * pitchQ;
    }

    Quaternion Quaternion::AngleAxis(const Vec3& axis, float angleDegrees)
    {
        float angleRadians = Math::toRadians(angleDegrees);
        float sine = std::sin(angleRadians / 2.0f);
        float cosine = std::cos(angleRadians / 2.0f);

        Vec3 axisN = Math::normalize(axis);
        return Quaternion{ cosine, axisN * sine };
    }

    Quaternion Quaternion::LookRotation(const Vec3& forward, const Vec3& up)
    {
        Vec3 zAxis = Math::normalize(forward);
        Vec3 xAxis = Math::normalize(Math::cross(up, zAxis));
        Vec3 yAxis = Math::cross(zAxis, xAxis);

        float t = 1.0f + xAxis.x + yAxis.y + zAxis.z;
        float s;
        Quaternion q;
        if (t > std::numeric_limits<float>::epsilon())
        {
            s = std::sqrt(t) * 2.0f;
            q.x = (yAxis.z - zAxis.y) / s;
            q.y = (zAxis.x - xAxis.z) / s;
            q.z = (xAxis.y - yAxis.x) / s;
            q.w = 0.25f * s;
        }
        else if(xAxis.x > yAxis.y && xAxis.x > zAxis.z)
        {
            t = 1.0f + xAxis.x - yAxis.y - zAxis.z;
            s = std::sqrt(t) * 2.0f;
            q.x = 0.25f * s;
            q.y = (xAxis.y + yAxis.x) / s;
            q.z = (zAxis.z + xAxis.z) / s;
            q.w = (yAxis.z - zAxis.y) / s;
        }
        else if (yAxis.y > zAxis.z)
        {
            t = 1.0f + yAxis.y - xAxis.x - zAxis.z;
            s = std::sqrt(t) * 2.0f;
            q.x = (xAxis.y + yAxis.x) / s;
            q.y = 0.25f * s;
            q.z = (yAxis.z + zAxis.y) / s;
            q.w = (zAxis.x - xAxis.z) / s;
        }
        else
        {
            t = 1.0f + zAxis.z - xAxis.x - yAxis.y;
            s = std::sqrt(t) * 2.0f;
            q.x = (zAxis.x + xAxis.z) / s;
            q.y = (yAxis.z + zAxis.y) / s;
            q.z = 0.25f * s;
            q.w = (xAxis.y - yAxis.x) / s;
        }

        return q;
    }

    Quaternion::Quaternion(float w, float x, float y, float z):
        w{ w }, v{ x, y, z }
    {

    }

    Quaternion::Quaternion(float w, const Vec3& vec):
        w{ w }, v{ vec }
    {

    }

    Quaternion::Quaternion(const Vec3& vec):
        Quaternion{ 0.0f, vec }
    {

    }
}