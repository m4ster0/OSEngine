#include "OSE/Events/EventWindow.h"
#include "OSE/Events/EventPlatform.h"
#include "OSE/Platform.h"
#include "OSE/Game.h"

#include <android_native_app_glue.h>

struct android_app* g_Application;

namespace OSE {

    PlatformType Platform::GetPlatformType()
    {
        return PlatformType::OS_ANDROID;
    }

    bool Platform::Initialize()
    {
        return true;
    }

    void Platform::OnWindowCreate()
    {
        m_WindowHandle = (void*)::g_Application->window;
        if(m_WindowHandle == nullptr)
            return;

        bool ctxRecreated = m_GraphicsDevice->Initialize(m_WindowHandle, {});
        m_WindowSCHandle = m_GraphicsDevice->CreateSwapChain(m_WindowHandle);
        m_GraphicsDevice->MakeCurrent(m_WindowSCHandle);

        if (ctxRecreated)
            m_Game->OnLoad();
    }

    void Platform::OnWindowDestroy()
    {
        if (m_WindowHandle)
        {
            m_GraphicsDevice->DestroySwapChain(m_WindowSCHandle);
            m_WindowSCHandle = 0;
            m_WindowHandle = nullptr;
        }
    }

    bool Platform::InternalUpdate()
    {
        int identifier;
        int events;
        struct android_poll_source* source;

        while ((identifier=ALooper_pollAll(m_Running ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
        {
            if (source != NULL)
                source->process(g_Application, source);

            if (g_Application->destroyRequested != 0)
                return false;
        }

        return true;
    }

    struct PlatformCommands
    {
        int32_t cmd;
    };

    bool handlePlatformCommands(const PlatformCommands& cmds)
    {
        Platform& platform = Platform::Instance();

        switch(cmds.cmd)
        {
            case APP_CMD_LOW_MEMORY:
                return true;
            case APP_CMD_INIT_WINDOW:
                platform.OnWindowCreate();
                return true;
            case APP_CMD_TERM_WINDOW:
                platform.OnWindowDestroy();
                return true;
            case APP_CMD_WINDOW_RESIZED:
//                platform.GetWindow().OnSizeChanged().Invoke(OSE::WindowResizeEvent{ 0, 0 });
                return true;
            case APP_CMD_GAINED_FOCUS:
                platform.GetEventBus().Dispatch(WindowFocusEvent{ true });
                platform.OnResume();
                return true;
            case APP_CMD_LOST_FOCUS:
                platform.OnPause();
                platform.GetEventBus().Dispatch(WindowFocusEvent{ false });
                return true;
        }

        return false;
    }
}

void handle_cmd(struct android_app*, int32_t cmd)
{
    OSE::handlePlatformCommands(OSE::PlatformCommands{ cmd });
}

int32_t handle_input(struct android_app* application, AInputEvent* event)
{
    return 0;
}