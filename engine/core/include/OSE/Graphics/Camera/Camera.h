#pragma once

#include "OSE/Math/Math.h"

namespace OSE {

    class Camera
    {
    public:
        Vec3 position;
        Vec3 target;
        Vec3 up;

        void UpdateView();

        void SetOrthographic(float left, float right, float top, float bottom, float near, float far);
        void SetPerspective(float fovDeg, float aspectRatio, float near, float far);

        inline const Mat4& GetView() const { return m_View; }
        inline const Mat4& GetProjection() const { return m_Projection; }
    private:

        Mat4 m_View;
        Mat4 m_Projection;
    };

}