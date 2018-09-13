#include "OSE/Graphics/GLDevice.h"
#include "OSE/Graphics/GLRenderer.h"

namespace OSE {

    std::unique_ptr<GraphicsRenderer> GLDevice::CreateRenderer()
    {
        GLContext* context = static_cast<GLContext*>(m_ImmediateContext.get());
        return std::unique_ptr<GraphicsRenderer>{ new GLRenderer{context}  };
    }

    GraphicsAPI GLDevice::GetAPI()
    {
        return GraphicsAPI::OPENGL;
    }

}