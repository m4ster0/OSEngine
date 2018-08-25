#include "OSE/Graphics/GLDevice.h"
#include "Win32GLContext.h"

namespace OSE {

    std::unique_ptr<GraphicsContext> GLDevice::CreateContextInternal()
    {
        return std::unique_ptr<GraphicsContext>{ new Win32GLContext };
    }

}