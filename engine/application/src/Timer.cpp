#include "OSE/System/Timer.h"

namespace OSE
{
	Timer::Timer(std::function<clock::time_point()> clockCallback):
        m_ClockCallback{ clockCallback }, m_Update{ clockCallback() }
	{
	}

	Timer::~Timer()
	{
	}

	bool Timer::Tick()
	{
		m_GameTime.total.m_Duration += m_AccTime.m_Duration;
		m_GameTime.delta.m_Duration = m_AccTime.m_Duration;
		m_GameTime.lag.m_Duration = TimeStep::duration::zero();

		m_AccTime.m_Duration = TimeStep::duration::zero();

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
		auto current = m_ClockCallback();
        TimeStep::duration elapsedTime{ current - m_Update };
		m_AccTime.m_Duration += elapsedTime;
		m_Update = current;
	}

	void Timer::Reset()
	{
		m_Update = m_ClockCallback();
		m_GameTime = GameTime{ };
	}
}