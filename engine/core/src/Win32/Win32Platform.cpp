#include <Windows.h>

#include "OSE/Platform.h"
#include "OSE/Game.h"
#include "OSE/Log.h"

#include "OSE/Events/EventWindow.h"
#include "OSE/Events/EventPlatform.h"

HINSTANCE g_hInstance;
WNDCLASSEX g_WindowClass;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace OSE {

	PlatformType Platform::GetPlatformType()
	{
		return PlatformType::OS_WIN32;
	}

    bool Platform::Initialize()
    {
        g_WindowClass = {};
        g_WindowClass.cbSize = sizeof(WNDCLASSEX);
        g_WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        g_WindowClass.lpfnWndProc = WndProc;
        g_WindowClass.hInstance = g_hInstance;
        g_WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        g_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        g_WindowClass.lpszClassName = "OSEWindow";
        g_WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        ATOM windowClassUId = RegisterClassEx(&g_WindowClass);
        OSE_ASSERT(windowClassUId, "Failed to register window class");


        // wrap in some method potentially
        HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
            g_WindowClass.lpszClassName, "Example Window",
            WS_OVERLAPPEDWINDOW,
            GetSystemMetrics(SM_CXSCREEN) / 2 - 800 / 2,
            GetSystemMetrics(SM_CYSCREEN) / 2 - 480 / 2,
            800, 480,
            NULL, NULL, g_WindowClass.hInstance, NULL);

        OSE_ASSERT(hwnd, "Failed to create window")

        m_WindowHandle = (void*) hwnd;

        ShowWindow((HWND) m_WindowHandle, SW_SHOW);
        SetFocus((HWND) m_WindowHandle);
        // ----

        return true;
    }

    void Platform::OnWindowCreate()
    {
        m_GraphicsDevice->Initialize(m_WindowHandle);

        m_WindowSCHandle = m_GraphicsDevice->CreateSwapChain(m_WindowHandle);
        m_GraphicsDevice->MakeCurrent(m_WindowSCHandle);
        m_Game->OnLoad();
    }

    void Platform::OnWindowDestroy()
    {
        if (m_WindowHandle)
        {
            m_GraphicsDevice->DestroySwapChain(m_WindowSCHandle);
            m_WindowSCHandle = 0;

            DestroyWindow((HWND)m_WindowHandle);
            m_WindowHandle = nullptr;
        }
    }

    bool Platform::InternalUpdate()
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true;
    }

    struct PlatformCommands
    {
        HWND hWnd;
        UINT message;
        WPARAM wParam;
        LPARAM lParam;
    };

    bool handlePlatformCommands(const PlatformCommands& cmds)
    {
        Platform& platform = Platform::Instance();

        if (cmds.hWnd && (HWND) platform.m_WindowHandle != cmds.hWnd)
            return false;

        switch (cmds.message)
        {
        case WM_SETFOCUS:
            platform.GetEventBus().Dispatch(OSE::WindowFocusEvent{ true });
            platform.OnResume();
            return true;
        case WM_KILLFOCUS:
            platform.OnPause();
            platform.GetEventBus().Dispatch(OSE::WindowFocusEvent{ false });
            return true;
        case WM_SIZE:
        {
            uint w = LOWORD(cmds.lParam);
            uint h = HIWORD(cmds.lParam);
            platform.GetEventBus().Dispatch(OSE::WindowResizeEvent{ w, h });
            return true;
        }
        case WM_CLOSE:
            platform.OnPause();
            platform.m_ShouldClose = true;
            return true;
        }

        return false;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = NULL;

    if (!OSE::handlePlatformCommands(OSE::PlatformCommands{ hWnd, message, wParam, lParam }))
        result = DefWindowProc(hWnd, message, wParam, lParam);

    return result;
}