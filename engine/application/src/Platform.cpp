#include "OSE/Platform.h"
#include "OSE/Log.h"

namespace OSE {

    Platform* Platform::s_Instance = nullptr;

    Platform::Platform(std::unique_ptr<Game> game, std::unique_ptr<GraphicsDevice> graphicsDevice) :
        m_Game{ std::move(game) }, m_GraphicsDevice{ std::move(graphicsDevice) }
    {
        OSE_ASSERT(s_Instance == nullptr, "Platform Instance already initialized");
        s_Instance = this;
    }

    Platform::~Platform()
    {

    }

    int Platform::Run()
    {
        if (!Initialize())
            return 1;

        m_Game->OnStart();
        OnWindowCreate();

        while (true)
        {
            if (!InternalUpdate() || m_ShouldClose) //exit signal from game dispatched potentially
            {
                m_Game->OnExit();
                m_GraphicsDevice->Terminate(); //destroying all graphics resources
                //OnWindowDestroy();
                return 0;
            }

            //main loop
            if (m_Running || false) //implement suspend policy in game potentially
            {
                m_Timer.Update();

                if (m_Game->IsFixedTimeStep())
                {
                    TimeStep target = m_Game->GetTargetTimeStep();
                    while (m_Timer.Tick(target))
                        m_Game->OnUpdate(m_Timer.GetGameTime());
                }
                else
                {
                    m_Timer.Tick();
                    m_Game->OnUpdate(m_Timer.GetGameTime());
                }

                m_Game->OnRender(m_Timer.GetGameTime());
                m_GraphicsDevice->Present(m_WindowSCHandle);
            }
        }
    }

    void Platform::OnResume()
    {
        if (!m_Running)
        {
            m_Running = true;
            m_Game->OnResume();
        }
    }

    void Platform::OnPause()
    {
        if (m_Running)
        {
            m_Running = false;
            m_Game->OnPause();
        }
    }

}