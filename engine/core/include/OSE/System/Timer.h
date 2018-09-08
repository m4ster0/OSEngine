#pragma once

#include "OSE/System/TimeStep.h"

#include <chrono>
#include <functional>

namespace OSE
{
    struct GameTime
    {
        TimeStep delta;
        TimeStep lag;
        TimeStep total;
    };

    class Timer
    {
    public:
        using clock = std::chrono::steady_clock;

        // inject clock callback for mock testing
        Timer(std::function<clock::time_point()> clockCallback = clock::now);
        ~Timer();

        inline const GameTime& GetGameTime() const { return m_GameTime; }

        bool Tick();
        bool Tick(TimeStep target);

        void Update();
        void Reset();

    private:
        std::function<clock::time_point()> m_ClockCallback;
        clock::time_point m_Update;
        TimeStep m_AccTime;
        GameTime m_GameTime;
    };
}
