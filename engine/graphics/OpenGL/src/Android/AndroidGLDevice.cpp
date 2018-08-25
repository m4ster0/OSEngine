#include "OSE/Graphics/GLDevice.h"
#include "AndroidGLContext.h"

namespace OSE {

    std::unique_ptr<GraphicsContext> GLDevice::CreateContextInternal()
    {
        return std::unique_ptr<GraphicsContext>{ new AndroidGLContext };
    }

}