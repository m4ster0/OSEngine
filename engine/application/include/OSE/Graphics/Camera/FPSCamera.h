#pragma once

#include "OSE/Graphics/Camera/Camera.h"

namespace OSE {

    class FPSCamera : public Camera
    {
    public:
        float pitch;
        float yaw;
        float roll;

        void UpdateView();

        void Translate(const Vec3& translation);
        void Translate(float x, float y, float z);
    };

}