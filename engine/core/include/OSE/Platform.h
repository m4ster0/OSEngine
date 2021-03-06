#pragma once

#include "OSE/Events/EventBus.h"
#include "OSE/System/Timer.h"
#include "OSE/Input.h"
#include "OSE/Game.h"
#include "OSE/Graphics/GraphicsDevice.h"
#include "OSE/Graphics/ResourceID.h"
#include "OSE/TypeDefs.h"

#include <string>

namespace OSE {

	enum class PlatformType
	{
		OS_WIN32,
		OS_ANDROID
	};

    struct WindowProperties
    {
        bool focused{ false };
        uint width;
        uint height;
    };

    struct PlatformCommands;

	class Platform
    {
    public:
		inline static Platform& Instance() { return *s_Instance; }

		Platform(std::unique_ptr<Game> game, std::unique_ptr<GraphicsDevice> graphicsDevice);
		~Platform();

		int Run();

        inline GraphicsDevice& GetGraphicsDevice() const { return *m_GraphicsDevice; }
        inline SwapChainHandle GetWindowSCHandle() const { return m_WindowSCHandle; }
        inline const WindowProperties& GetWindowProps() const { return m_WindowProperties; }
        inline Input& GetInput() const { return *m_Input; }

        inline EventBus& GetEventBus() { return m_EventBus; }
        inline Timer& GetTimer() { return m_Timer; }
		PlatformType GetPlatformType();

    private:
        static Platform* s_Instance;

        std::unique_ptr<Game> m_Game{ nullptr };
        bool m_Running{ false };
        bool m_ShouldClose{ false };

        // Window members
        void* m_WindowHandle{ nullptr };
        WindowProperties m_WindowProperties;

        std::unique_ptr<GraphicsDevice> m_GraphicsDevice{ nullptr };
        SwapChainHandle m_WindowSCHandle{ 0 };

        std::unique_ptr<Input> m_Input{ nullptr };

        EventBus m_EventBus;
        Timer m_Timer;

        bool Initialize();
        bool InternalUpdate();

        void OnWindowCreate();
        void OnWindowDestroy();
        void OnResume();
        void OnPause();

        friend bool handleWindowCommands(const PlatformCommands& cmds);
        friend bool handleInputCommands(const PlatformCommands& cmds);
	};

}
