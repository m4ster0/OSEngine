#pragma once

#include <OSE/Graphics/GraphicsContext.h>
#include <OSE/Graphics/Resource.h>

#include <unordered_map>
#include <memory>

#include <EGL/egl.h>

namespace OSE {
    class AndroidGLContext : public GraphicsContext
    {
        friend class GLDevice;

        struct AndroidGLSwapChain : public Resource<AndroidGLSwapChain>
        {
            EGLDisplay display{ EGL_NO_DISPLAY };
            EGLSurface surface{ EGL_NO_SURFACE };

            ~AndroidGLSwapChain()
            {
                Dispose();
            }

            void Dispose() override
            {
                if (surface != EGL_NO_SURFACE)
                    eglDestroySurface(display, surface);
            }
        };

        EGLDisplay m_Display{ EGL_NO_DISPLAY };
        EGLContext m_Context{ EGL_NO_CONTEXT };
        EGLConfig m_Config{ nullptr };

        std::unordered_map<ResourceID, std::unique_ptr<AndroidGLSwapChain>, ResourceID::Hasher> m_SwapChains;

    public:
        ~AndroidGLContext();
        virtual bool IsValid() override;

        virtual ResourceID CreateSwapChain(void* windowHandle) override;
        virtual void DestroySwapChain(ResourceID handle) override;

        virtual bool MakeCurrent(ResourceID handle) override;
        virtual bool Present(ResourceID handle) override;

    protected:
        AndroidGLContext();
    };
}