#pragma once

#include "OSE/Graphics/GLContext.h"

#include <OSE/Graphics/GraphicsResource.h>

#include <unordered_map>
#include <memory>

#include "Windows.h"

namespace OSE {
    class Win32GLContext : public GLContext
    {
        friend class GLDevice;

        struct Win32GLSwapChain
        {
            HWND windowHandle{ NULL };
            HDC windowDC{ NULL };

            Win32GLSwapChain() = default;

            Win32GLSwapChain(const Win32GLSwapChain&) = delete;
            Win32GLSwapChain(Win32GLSwapChain&&) = delete;

            Win32GLSwapChain& operator=(const Win32GLSwapChain&) = delete;
            Win32GLSwapChain& operator=(Win32GLSwapChain&&) = delete;

            ~Win32GLSwapChain()
            {
                Dispose();
            }

            void Dispose()
            {
                ReleaseDC(windowHandle, windowDC);
                windowHandle = NULL;
                windowDC = NULL;
            }
        };

        HGLRC m_HRC{ NULL };
        PIXELFORMATDESCRIPTOR m_PixelFormatDescriptor;
        int m_PixelFormat{ 0 };

        std::unordered_map<SwapChainHandle, std::unique_ptr<Win32GLSwapChain>> m_SwapChains;

    public:
        ~Win32GLContext();
        virtual bool IsValid() override;

        virtual SwapChainHandle CreateSwapChain(void* windowHandle) override;
        virtual void DestroySwapChain(SwapChainHandle handle) override;

        virtual bool MakeCurrent(SwapChainHandle handle) override;
        virtual bool Present(SwapChainHandle handle) override;

        virtual void Terminate() override;

    protected:
        Win32GLContext();
    };
}