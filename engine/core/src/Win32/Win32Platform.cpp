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

        m_WindowProperties.width = 800;
        m_WindowProperties.height = 480;

        // wrap in some method potentially
        HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
            g_WindowClass.lpszClassName, "Example Window",
            WS_OVERLAPPEDWINDOW,
            GetSystemMetrics(SM_CXSCREEN) / 2 - m_WindowProperties.width / 2,
            GetSystemMetrics(SM_CYSCREEN) / 2 - m_WindowProperties.height / 2,
            m_WindowProperties.width, m_WindowProperties.height,
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
        m_GraphicsDevice->Initialize(m_WindowHandle, {});

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
        while (PeekMessage(&msg, (HWND) m_WindowHandle, 0, 0, PM_REMOVE))
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

    bool handleWindowCommands(const PlatformCommands& cmds)
    {
        Platform& platform = Platform::Instance();

        switch (cmds.message)
        {
        case WM_SETFOCUS:
            platform.m_WindowProperties.focused = true;
            platform.GetEventBus().Dispatch(OSE::WindowFocusEvent{ true });
            platform.OnResume();
            return true;
        case WM_KILLFOCUS:
            platform.OnPause();
            platform.m_WindowProperties.focused = false;
            platform.GetEventBus().Dispatch(OSE::WindowFocusEvent{ false });
            return true;
        case WM_SIZE:
        {
            uint w = LOWORD(cmds.lParam);
            uint h = HIWORD(cmds.lParam);
            platform.m_WindowProperties.width = w;
            platform.m_WindowProperties.height = h;
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

    namespace {
        inline KeyboardEvent::Key convertKey(uint vKeyCode);
    }

    bool handleInputCommands(const PlatformCommands& cmds)
    {
        Platform& platform = Platform::Instance();
        Input& input = platform.GetInput();
        switch (cmds.message)
        {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            KeyboardEvent::Key key = convertKey(cmds.wParam);
            input.m_Keys[static_cast<uint8>(key)] = true;
            bool repeated = (cmds.lParam >> 30) & 1;
            if (!repeated)
            {

            }
        case WM_KEYUP:
        case WM_SYSKEYUP:
            return true;
        }

        return false;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    OSE::PlatformCommands cmds{ hWnd, message, wParam, lParam };
    if (OSE::handleWindowCommands(cmds) || OSE::handleInputCommands(cmds))
        return NULL;

    return DefWindowProc(hWnd, message, wParam, lParam);;
}