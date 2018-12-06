#pragma once

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
            return degrees / 180.0 * pi;
        }

        inline float toDegrees(float radians)
        {
            return radians / pi * 180.0f;
        }

        inline double toDegrees(double radians)
        {
            return radians / pi * 180.0;
        }

        template<typename FP>
        using FPEnabled = std::enable_if_t<std::is_floating_point<FP>::value>;

        template<typename I>
        using IEnabled = std::enable_if_t<std::is_integral<I>::value>;
    }
}