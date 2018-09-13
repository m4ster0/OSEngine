#include "OSE/Graphics/GraphicsDevice.h"

#include <utility>

namespace OSE {

    SwapChainHandle GraphicsDevice::CreateSwapChain(void* windowHandle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->CreateSwapChain(windowHandle);

        return 0;
    }

    bool GraphicsDevice::MakeCurrent(SwapChainHandle handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->MakeCurrent(handle);

        return false;
    }

    bool GraphicsDevice::Present(SwapChainHandle handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->Present(handle);

        return false;
    }

    void GraphicsDevice::DestroySwapChain(SwapChainHandle handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            m_ImmediateContext->DestroySwapChain(handle);
    }

    std::unique_ptr<GraphicsResourceProxy> GraphicsDevice::CreateResourceProxy()
    {
        return std::unique_ptr<GraphicsResourceProxy>{ new GraphicsResourceProxy{ m_ImmediateContext.get() } };
    }

    bool GraphicsDevice::Initialize()
    {
        if (m_ImmediateContext == nullptr || !m_ImmediateContext->IsValid())
        {
            Terminate();
            InitializeInternal();
            return true;
        }

        return false;
    }

    void GraphicsDevice::Terminate()
    {
        if (m_ImmediateContext)
            m_ImmediateContext->Terminate();

        m_ImmediateContext = nullptr;
    }
}