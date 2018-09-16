#pragma once

#include "OSE/Graphics/GLContext.h"

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

            Win32GLSwapChain(Win32GLSwapChain&&) = delete;
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

        SwapChainHandle m_ActiveSwapChain;
        std::unordered_map<SwapChainHandle, std::unique_ptr<Win32GLSwapChain>> m_SwapChains;

    public:
        ~Win32GLContext();
        bool IsValid() override;

        SwapChainHandle CreateSwapChain(void* windowHandle) override;
        void DestroySwapChain(SwapChainHandle handle) override;

        bool MakeCurrent(SwapChainHandle handle) override;
        bool Present(SwapChainHandle handle) override;

        void Dispose() override;

    protected:
        Win32GLContext();
    };
}