
#include "OSE/Graphics/Camera/Camera.h"


namespace OSE {

    Camera::Camera():
        Camera{ Vec3::Zero, Quaternion::Identity }
    {
    }

    Camera::Camera(const Vec3& position):
        Camera{ position, Quaternion::Identity }
    {
    }

    Camera::Camera(const Vec3 & position, const Quaternion & rotation):
        position{ position }, direction{ rotation }
    {
    }

    void OSE::Camera::UpdateView()
    {
        m_View = Math::lookAt(position, direction);
        UpdateViewProjection();
    }

    void Camera::SetOrthographic(float left, float right, float bottom, float top, float near, float far)
    {
        m_Projection = Math::orthographic(left, right, bottom, top, near, far);
        UpdateViewProjection();
    }

    void Camera::SetPerspective(float fovDegrees, float aspectRatio, float near, float far)
    {
        m_Projection = Math::perspective(fovDegrees, aspectRatio, near, far);
        UpdateViewProjection();
    }

    void Camera::UpdateViewProjection()
    {
        m_ViewProjection = m_View * m_Projection;
    }

}