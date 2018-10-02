#include "OSE/Graphics/GLDevice.h"
#include "AndroidGLContext.h"

namespace OSE {

    void GLDevice::CreateContextInternal(void* windowHandle)
    {
        m_ImmediateContext = std::unique_ptr<GLContext>( new AndroidGLContext(windowHandle) );
    }
}