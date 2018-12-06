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

        GraphicsResourceProxy* GetResourceProxy() override;
        GraphicsRenderer* GetRenderer() override;
        const GraphicsConfig* GetCurrentConfig() const override;
        GraphicsAPI GetAPI() const override;
    protected:
        std::unique_ptr<GLContext> m_ImmediateContext{ nullptr };

        bool Initialize(const void* windowHandle, const GraphicsConfig& config) override;
        void Terminate() override;

        void CreateContextInternal(const void* windowHandle, const GraphicsConfig& config);
    };

}
