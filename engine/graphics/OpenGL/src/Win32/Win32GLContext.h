#pragma once

#include <OSE/Graphics/GraphicsContext.h>
#include <OSE/Graphics/Resource.h>

#include <unordered_map>
#include <memory>

#include "Windows.h"

namespace OSE {
    class Win32GLContext : public GraphicsContext
    {
        friend class GLDevice;

        struct Win32GLSwapChain : public Resource<Win32GLSwapChain>
        {
            HWND windowHandle{ NULL };
            HDC windowDC{ NULL };

            void Dispose() override
            {
                ReleaseDC(windowHandle, windowDC);
                windowHandle = NULL;
                windowDC = NULL;
            }
        };

        HGLRC m_HRC{ NULL };
        PIXELFORMATDESCRIPTOR m_PixelFormatDescriptor;
        int m_PixelFormat{ 0 };

        std::unordered_map<ResourceID, std::unique_ptr<Win32GLSwapChain>, ResourceID::Hasher> m_SwapChains;

    public:
        ~Win32GLContext();
        virtual bool IsValid() override;

        virtual ResourceID CreateSwapChain(void* windowHandle) override;
        virtual void DestroySwapChain(ResourceID handle) override;

        virtual bool MakeCurrent(ResourceID handle) override;
        virtual bool Present(ResourceID handle) override;

    protected:
        Win32GLContext();
    };
}