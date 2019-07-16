#pragma once

#include "OSE/Math/Math.h"

namespace OSE {

    class Camera
    {
    public:
        Vec3 position;
        Quaternion direction;

        Camera();
        Camera(const Vec3& position);
        Camera(const Vec3& position, const Quaternion& rotation);

        void UpdateView();

        void SetOrthographic(float left, float right, float top, float bottom, float near, float far);
        void SetPerspective(float fovDegrees, float aspectRatio, float near, float far);

        inline const Mat4& GetView() const { return m_View; }
        inline const Mat4& GetProjection() const { return m_Projection; }
        inline const Mat4& GetViewProjection() const { return m_ViewProjection; }
    private:
        Mat4 m_View;
        Mat4 m_Projection;
        Mat4 m_ViewProjection;

        void UpdateViewProjection();
    };

}