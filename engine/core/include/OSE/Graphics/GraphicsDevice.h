#pragma once

#include "OSE/Graphics/GraphicsContext.h"
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

        SwapChainHandle CreateSwapChain(void* windowHandle);
        bool MakeCurrent(SwapChainHandle handle);
        bool Present(SwapChainHandle handle);
        void DestroySwapChain(SwapChainHandle handle);

        std::unique_ptr<GraphicsResourceProxy> CreateResourceProxy();
        virtual std::unique_ptr<GraphicsRenderer> CreateRenderer() = 0;

    protected:
        std::unique_ptr<GraphicsContext> m_ImmediateContext;

        virtual void InitializeInternal() = 0;
        virtual GraphicsAPI GetAPI() = 0;

    private:
        bool Initialize();
        void Terminate();
    };

}
