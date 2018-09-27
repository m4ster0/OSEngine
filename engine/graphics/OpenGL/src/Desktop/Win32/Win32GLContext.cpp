#include "Win32GLContext.h"
#include "OSE/Graphics/GLCommon.h"

#include <OSE/Log.h>

extern WNDCLASSEX g_WindowClass;

namespace OSE {

    static HWND GetDummyWindowHandle()
    {
        return CreateWindowEx(0,
            g_WindowClass.lpszClassName, "",
            0,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, g_WindowClass.hInstance, NULL);
    }

    Win32GLContext::Win32GLContext()
    {
        HWND dummyHWND = GetDummyWindowHandle();
        HDC dummyHDC = GetDC(dummyHWND);

        m_PixelFormatDescriptor.nSize        = sizeof(m_PixelFormatDescriptor);
        m_PixelFormatDescriptor.nVersion     = 1;
        m_PixelFormatDescriptor.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        m_PixelFormatDescriptor.iPixelType   = PFD_TYPE_RGBA;
        m_PixelFormatDescriptor.cColorBits   = 32;
        m_PixelFormatDescriptor.cAlphaBits   = 8;

        m_PixelFormat = ChoosePixelFormat(dummyHDC, &m_PixelFormatDescriptor);
        OSE_ASSERT(m_PixelFormat, "Pixel format not found");

        BOOL spf = SetPixelFormat(dummyHDC, m_PixelFormat, &m_PixelFormatDescriptor);
        OSE_ASSERT(spf, "Pixel format set failed");

        DescribePixelFormat(dummyHDC, m_PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &m_PixelFormatDescriptor);

        m_HRC = wglCreateContext(dummyHDC);
        OSE_ASSERT(m_HRC, "Opengl context could not be created");

        BOOL activeHRC = wglMakeCurrent(dummyHDC, m_HRC);
        OSE_ASSERT(activeHRC, "Opengl context could not be set as current");

        int glad = gladLoadGL();
        OSE_ASSERT(glad, "Failed to init glad");

        //std::cout << glGetString(GL_VERSION) << std::endl;
        //std::cout << "-----------" << std::endl;

        wglMakeCurrent(dummyHDC, NULL);
        ReleaseDC(dummyHWND, dummyHDC);
        DestroyWindow(dummyHWND);
    }

    Win32GLContext::~Win32GLContext()
    {
        if (m_ActiveSwapChain)
            wglMakeCurrent(NULL, NULL);

        if(m_HRC)
            wglDeleteContext(m_HRC);

        m_SwapChains.clear();
    }

    bool Win32GLContext::IsValid()
    {
        return m_HRC != NULL;
    }

    SwapChainHandle Win32GLContext::CreateSwapChain(void* windowHandle)
    {
        static SwapChainHandle Counter{ 0 };

        HWND handle = (HWND)windowHandle;

        std::unique_ptr<Win32GLSwapChain> swapChain{ new Win32GLSwapChain };
        swapChain->windowHandle = handle;
        swapChain->windowDC = GetDC(handle);

        SwapChainHandle rid = 0;
        if (SetPixelFormat(swapChain->windowDC, m_PixelFormat, &m_PixelFormatDescriptor))
        {
            rid = ++Counter;
            m_SwapChains[rid] = std::move(swapChain);
        }

        return rid;
    }

    void Win32GLContext::DestroySwapChain(SwapChainHandle handle)
    {
        if (m_SwapChains.find(handle) != m_SwapChains.end())
        {
            if (handle == m_ActiveSwapChain)
            {
                wglMakeCurrent(NULL, NULL);
                m_ActiveSwapChain = 0;
            }

            m_SwapChains.erase(handle);
        }
    }

    bool Win32GLContext::MakeCurrent(SwapChainHandle handle)
    {
        if (handle)
        {
            if (handle == m_ActiveSwapChain)
                return true;

            if (m_SwapChains.find(handle) != m_SwapChains.end() && wglMakeCurrent(m_SwapChains[handle]->windowDC, m_HRC))
            {
                m_ActiveSwapChain = handle;
                return true;
            }
        }

        return false;
    }

    bool Win32GLContext::Present(SwapChainHandle handle)
    {
        if (handle && handle == m_ActiveSwapChain)
        {
            return SwapBuffers(m_SwapChains[handle]->windowDC);
        }

        return false;
    }

    void Win32GLContext::Dispose()
    {
        GLContext::Dispose();
        m_SwapChains.clear();
    }
}