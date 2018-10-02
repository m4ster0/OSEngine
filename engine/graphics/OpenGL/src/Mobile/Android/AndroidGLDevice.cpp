#include "OSE/Graphics/GLDevice.h"
#include "AndroidGLContext.h"

namespace OSE {

    void GLDevice::CreateContextInternal(const void* windowHandle, const GraphicsConfig& config)
    {
        m_ImmediateContext = std::unique_ptr<GLContext>( new AndroidGLContext(windowHandle, config) );
    }
}