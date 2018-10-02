#pragma once

#include "OSE/Graphics/GLContext.h"

#include <unordered_map>
#include <memory>

#include <EGL/egl.h>

namespace OSE {
    class AndroidGLContext : public GLContext
    {
        friend class GLDevice;

        struct AndroidGLSwapChain
        {
            EGLDisplay display{ EGL_NO_DISPLAY };
            EGLSurface surface{ EGL_NO_SURFACE };

            ~AndroidGLSwapChain()
            {
                Dispose();
            }

            void Dispose()
            {
                if (surface != EGL_NO_SURFACE)
                    eglDestroySurface(display, surface);
            }
        };

        EGLDisplay m_Display{ EGL_NO_DISPLAY };
        EGLContext m_Context{ EGL_NO_CONTEXT };
        EGLConfig m_Config{ nullptr };

        SwapChainHandle m_ActiveSwapChain;
        std::unordered_map<SwapChainHandle, std::unique_ptr<AndroidGLSwapChain>> m_SwapChains;

    public:
        ~AndroidGLContext();
        bool IsValid() override;

        SwapChainHandle CreateSwapChain(void* windowHandle) override;
        void DestroySwapChain(SwapChainHandle handle) override;

        bool MakeCurrent(SwapChainHandle handle) override;
        bool Present(SwapChainHandle handle) override;

        void Dispose() override;

    protected:
        AndroidGLContext(const void* windowHandle, const GraphicsConfig& config);
    };
}