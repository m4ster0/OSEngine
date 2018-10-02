#include "OSE/Graphics/GLDevice.h"
#include "Win32GLContext.h"

namespace OSE {

    void GLDevice::CreateContextInternal(void* windowHandle)
    {
        m_ImmediateContext = std::unique_ptr<GLContext>( new Win32GLContext(windowHandle) );
    }

}