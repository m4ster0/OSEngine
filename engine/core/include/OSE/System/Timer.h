#pragma once

#include "OSE/System/TimeStep.h"

#include <chrono>

namespace OSE
{
	using namespace std::chrono;

    struct GameTime
    {
        TimeStep delta;
        TimeStep lag;
        TimeStep total;
    };

	class Timer
	{
	private:
		high_resolution_clock::time_point m_Update;
		TimeStep m_AccTime;
		GameTime m_GameTime;

	public:
		Timer();
		~Timer();

		inline const GameTime& GetGameTime() const { return m_GameTime; }

		bool Tick();
		bool Tick(TimeStep target);

		void Update();
		void Reset();
	};
}
