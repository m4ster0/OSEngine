#pragma once

#include "OSE/System/Timer.h"

namespace OSE {

	using namespace std::chrono_literals;

    class Game
    {
    protected:
        bool m_FixedTimeStep{ false };
        TimeStep m_TargetTimeStep{ 16.6ms };

    public:
        virtual ~Game() = default;

        virtual void OnStart() = 0;
        virtual void OnExit() = 0;

        virtual void OnLoad() { };

        virtual void OnResume() { };
        virtual void OnPause() { };

        virtual void OnUpdate(const GameTime& gameTime) = 0;
        virtual void OnRender(const GameTime& gameTime) = 0;

        inline bool IsFixedTimeStep() const { return m_FixedTimeStep; }
        inline TimeStep GetTargetTimeStep() const { return m_TargetTimeStep; }
    };
}