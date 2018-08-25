#include "OSE/System/Timer.h"

namespace OSE
{
	Timer::Timer():
		m_Update{ high_resolution_clock::now() }
	{
	}

	Timer::~Timer()
	{
	}

	bool Timer::Tick()
	{
		m_GameTime.total.m_Duration += m_AccTime.m_Duration;
		m_GameTime.delta.m_Duration = m_AccTime.m_Duration;
		m_GameTime.lag.m_Duration = duration<double>::zero();

		m_AccTime.m_Duration = duration<double>::zero();

		return true;
	}

	bool Timer::Tick(TimeStep target)
	{
		if (m_AccTime.m_Duration >= target.m_Duration)
		{
			m_AccTime.m_Duration -= target.m_Duration;

			m_GameTime.total.m_Duration += target.m_Duration;
			m_GameTime.delta.m_Duration = target.m_Duration;
			m_GameTime.lag.m_Duration = m_AccTime.m_Duration;

			return true;
		}

		return false;
	}

	void Timer::Update()
	{
		auto current = high_resolution_clock::now();
		duration<double> elapsedTime{ current - m_Update };
		m_AccTime.m_Duration += elapsedTime;
		m_Update = current;
	}

	void Timer::Reset()
	{
		m_Update = high_resolution_clock::now();
		m_GameTime = GameTime{ };
	}
}