
#include "OSE/Graphics/Camera/Camera.h"


namespace OSE {

    void OSE::Camera::UpdateView()
    {
        m_View = Math::lookAt(position, target, up);
    }

    void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
    {
        m_Projection = Math::orthographic(left, right, top, bottom, near, far);
    }

    void Camera::SetPerspective(float fovRadians, float aspectRatio, float near, float far)
    {
        m_Projection = Math::perspective(fovRadians, aspectRatio, near, far);
    }

}