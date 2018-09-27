#include "AndroidGLContext.h"

#include <OSE/Log.h>

#include <EGL/egl.h>

namespace OSE {

    AndroidGLContext::AndroidGLContext()
    {
        m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        eglInitialize(m_Display, 0, 0);

        const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
        };

        EGLint numConfigs;
        eglChooseConfig(m_Display, attribs, nullptr,0, &numConfigs);
        std::unique_ptr<EGLConfig[]> supportedConfigs{ new EGLConfig[numConfigs]};
        OSE_ASSERT(supportedConfigs, "no supported configs available");
        eglChooseConfig(m_Display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
//        assert(numConfigs);

        for (int i = 0; i < numConfigs; i++)
        {
            auto& cfg = supportedConfigs[i];
            EGLint r, g, b, d;
            if (eglGetConfigAttrib(m_Display, cfg, EGL_RED_SIZE, &r)   &&
                eglGetConfigAttrib(m_Display, cfg, EGL_GREEN_SIZE, &g) &&
                eglGetConfigAttrib(m_Display, cfg, EGL_BLUE_SIZE, &b)  &&
                eglGetConfigAttrib(m_Display, cfg, EGL_DEPTH_SIZE, &d) &&
                r == 8 && g == 8 && b == 8 && d == 0 ) {

                m_Config = supportedConfigs[i];
                break;
            }
        }

        if (m_Config == nullptr)
            m_Config = supportedConfigs[0];

        EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
        };

        m_Context = eglCreateContext(m_Display, m_Config, NULL, contextAttribs);

        //save somewhere version and available extensions
    }

    AndroidGLContext::~AndroidGLContext()
    {
        if (m_Context != EGL_NO_CONTEXT)
            eglDestroyContext(m_Display, m_Context);

        if (m_Display != EGL_NO_DISPLAY)
            eglTerminate(m_Display);
    }

    bool AndroidGLContext::IsValid()
    {
        if (m_Display == EGL_NO_DISPLAY || m_Context == EGL_NO_CONTEXT)
            return false;

        EGLint attribValue;
        if (eglQueryContext(m_Display, m_Context, EGL_CONFIG_ID, &attribValue) == EGL_FALSE)
        {
            return false;
        }

        return true;
    }

    SwapChainHandle AndroidGLContext::CreateSwapChain(void* windowHandle)
    {
        static SwapChainHandle Counter{ 0 };

        ANativeWindow* window = (ANativeWindow*) windowHandle;

        EGLint format;
        eglGetConfigAttrib(m_Display, m_Config, EGL_NATIVE_VISUAL_ID, &format);
//        ANativeWindow_setBuffersGeometry(window, 0, 0, format);

        std::unique_ptr<AndroidGLSwapChain> swapChain{ new AndroidGLSwapChain };
        swapChain->display = m_Display;
        swapChain->surface = eglCreateWindowSurface(m_Display, m_Config, window, NULL);

        SwapChainHandle rid = 0;
        if (swapChain->surface != NULL)
        {
            rid = ++Counter;
            m_SwapChains[rid] = std::move(swapChain);
        }

        return rid;
    }

    void AndroidGLContext::DestroySwapChain(SwapChainHandle handle)
    {
        if (m_SwapChains.find(handle) != m_SwapChains.end())
        {
            if (handle == m_ActiveSwapChain)
            {
                eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                m_ActiveSwapChain = 0;
            }

            m_SwapChains.erase(handle);
        }
    }

    bool AndroidGLContext::MakeCurrent(SwapChainHandle handle)
    {
        if (handle)
        {
            if (handle == m_ActiveSwapChain)
                return true;

            if ((m_SwapChains.find(handle) != m_SwapChains.end()) &&
                    eglMakeCurrent(m_SwapChains[handle]->display, m_SwapChains[handle]->surface, m_SwapChains[handle]->surface, m_Context) == EGL_TRUE)
            {
                m_ActiveSwapChain = handle;
                return true;
            }
        }

        return false;
    }

    bool AndroidGLContext::Present(SwapChainHandle handle)
    {
        if (handle && handle == m_ActiveSwapChain)
            return eglSwapBuffers(m_SwapChains[handle]->display, m_SwapChains[handle]->surface) == EGL_TRUE;

        return false;
    }
}