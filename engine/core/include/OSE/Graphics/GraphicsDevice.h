#pragma once

#include "OSE/Graphics/GraphicsResourceProxy.h"
#include "OSE/Graphics/GraphicsRenderer.h"
#include "OSE/Graphics/ResourceID.h"

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

        virtual SwapChainHandle CreateSwapChain(void* windowHandle) = 0;
        virtual bool MakeCurrent(SwapChainHandle handle) = 0;
        virtual bool Present(SwapChainHandle handle) = 0;
        virtual void DestroySwapChain(SwapChainHandle handle) = 0;

        virtual std::unique_ptr<GraphicsResourceProxy> CreateResourceProxy() = 0;
        virtual std::unique_ptr<GraphicsRenderer> CreateRenderer() = 0;
        virtual GraphicsAPI GetAPI() = 0;

    protected:
        virtual bool Initialize() = 0;
        virtual void Terminate() = 0;
    };

}
