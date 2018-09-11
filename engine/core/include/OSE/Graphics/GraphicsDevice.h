#pragma once

#include "OSE/Graphics/GraphicsContext.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/Graphics/ResourceCommandBuffer.h"
#include "OSE/TypeDefs.h"

#include <memory>
#include <unordered_map>

namespace OSE {

    enum class GraphicsAPI
    {
        OPENGL,
        DIRECTX11
    };

    class GraphicsDevice
    {
        friend class Platform;

    public:
        virtual ~GraphicsDevice() = default;

        ResourceID CreateSwapChain(void* windowHandle);

        bool MakeCurrent(ResourceID handle);
        bool Present(ResourceID handle);

        void DestroySwapChain(ResourceID handle);

        std::unique_ptr<ResourceCommandBuffer> CreateResourceCommandBuffer();

    protected:
        std::shared_ptr<GraphicsContext> m_ImmediateContext;

        virtual void CreateContextInternal() = 0;
        virtual GraphicsAPI GetAPI() = 0;

    private:
        bool Initialize();
        void Terminate();
    };

}
