#include "OSE/Graphics/GLDevice.h"
#include "Win32GLContext.h"

namespace OSE {

    void GLDevice::CreateContextInternal()
    {
        m_ImmediateContext = std::shared_ptr<GraphicsContext>{ new Win32GLContext };
    }

}