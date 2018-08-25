#pragma once

#include "OSE/Graphics/ResourceID.h"

namespace OSE {

    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;
        virtual bool IsValid() = 0;

        virtual ResourceID CreateSwapChain(void* windowHandle) = 0;
        virtual void DestroySwapChain(ResourceID handle) = 0;

        virtual bool MakeCurrent(ResourceID handle) = 0;
        virtual bool Present(ResourceID handle) = 0;

    protected:
        GraphicsContext() = default;

        ResourceID m_ActiveSwapChain{ };
    };

}
