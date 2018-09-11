#include "OSE/Graphics/GraphicsDevice.h"

#include <utility>

namespace OSE {

    ResourceID GraphicsDevice::CreateSwapChain(void* windowHandle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->CreateSwapChain(windowHandle);

        return ResourceID::Invalid;
    }

    bool GraphicsDevice::MakeCurrent(ResourceID handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->MakeCurrent(handle);

        return false;
    }

    bool GraphicsDevice::Present(ResourceID handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            return m_ImmediateContext->Present(handle);

        return false;
    }

    void GraphicsDevice::DestroySwapChain(ResourceID handle)
    {
        if (m_ImmediateContext && m_ImmediateContext->IsValid())
            m_ImmediateContext->DestroySwapChain(handle);
    }

    std::unique_ptr<ResourceCommandBuffer> GraphicsDevice::CreateResourceCommandBuffer()
    {
        return std::make_unique<ResourceCommandBuffer>(m_ImmediateContext);
    }

    bool GraphicsDevice::Initialize()
    {
        if (m_ImmediateContext == nullptr || !m_ImmediateContext->IsValid())
        {
            CreateContextInternal();
            return true;
        }

        return false;
    }

    void GraphicsDevice::Terminate()
    {
        m_ImmediateContext = nullptr;
    }
}