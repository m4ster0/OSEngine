#pragma once

#include <OSE/Graphics/GraphicsDevice.h>

#include "OSE/Graphics/GLContext.h"

#include <memory>

namespace OSE {

    class GLDevice : public GraphicsDevice
    {
    public:
        SwapChainHandle CreateSwapChain(void* windowHandle) override;
        bool MakeCurrent(SwapChainHandle handle) override;
        bool Present(SwapChainHandle handle) override;
        void DestroySwapChain(SwapChainHandle handle) override;

        std::unique_ptr<GraphicsResourceProxy> CreateResourceProxy() override;
        std::unique_ptr<GraphicsRenderer> CreateRenderer() override;
        GraphicsAPI GetAPI() override;
    protected:
        std::unique_ptr<GLContext> m_ImmediateContext{ nullptr };

        bool Initialize(void* windowHandle) override;
        void Terminate() override;

        void CreateContextInternal(void* windowHandle);
    };

}
