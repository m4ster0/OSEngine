#include "OSE/Graphics/GLDevice.h"
#include "OSE/Graphics/GLRenderer.h"
#include "OSE/Graphics/GLResourceProxy.h"

namespace OSE {

    GraphicsRenderer* GLDevice::GetRenderer()
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return &m_ImmediateContext->GetRenderer();

        return nullptr;
    }

    GraphicsResourceProxy* GLDevice::GetResourceProxy()
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return &m_ImmediateContext->GetResourceProxy();

        return nullptr;
    }

    SwapChainHandle GLDevice::CreateSwapChain(void* windowHandle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->CreateSwapChain(windowHandle);

        return 0;
    }

    bool GLDevice::MakeCurrent(SwapChainHandle handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->MakeCurrent(handle);

        return false;
    }

    bool GLDevice::Present(SwapChainHandle handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->Present(handle);

        return false;
    }

    void GLDevice::DestroySwapChain(SwapChainHandle handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            m_ImmediateContext->DestroySwapChain(handle);
    }

    GraphicsAPI GLDevice::GetAPI() const
    {
        return GraphicsAPI::OPENGL;
    }

    const GraphicsConfig* GLDevice::GetCurrentConfig() const
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return &m_ImmediateContext->GetConfig();

        return nullptr;
    }

    bool GLDevice::Initialize(const void* windowHandle, const GraphicsConfig& config)
    {
        if (m_ImmediateContext == nullptr || !m_ImmediateContext->IsValid())
        {
            Terminate();
            CreateContextInternal(windowHandle, config);
            return true;
        }

        return false;
    }

    void GLDevice::Terminate()
    {
        if (m_ImmediateContext)
            m_ImmediateContext->Dispose();

        m_ImmediateContext = nullptr;

    }
}