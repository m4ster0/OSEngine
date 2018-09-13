#include "OSE/Graphics/GLDevice.h"
#include "AndroidGLContext.h"

namespace OSE {

    void GLDevice::InitializeInternal()
    {
        m_ImmediateContext = std::unique_ptr<GraphicsContext>{ new AndroidGLContext };
    }

}