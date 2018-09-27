#pragma once

#include "OSE/Math/Math.h"

namespace OSE {

    class Camera
    {
    public:
        void Update();

    private:
        Vec3 position;
        Vec3 target;

        Mat4 m_View;
        Mat4 m_Projection;
    };

}