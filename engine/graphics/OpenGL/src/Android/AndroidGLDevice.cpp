#include "OSE/Graphics/GLDevice.h"
#include "AndroidGLContext.h"

namespace OSE {

    void GLDevice::CreateContextInternal()
    {
        m_ImmediateContext = std::shared_ptr<GraphicsContext>{ new AndroidGLContext };
    }

}