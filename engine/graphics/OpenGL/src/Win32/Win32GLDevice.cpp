#include "OSE/Graphics/GLDevice.h"
#include "Win32GLContext.h"

namespace OSE {

    void GLDevice::InitializeInternal()
    {
        m_ImmediateContext = std::unique_ptr<GraphicsContext>{ new Win32GLContext };
    }

}