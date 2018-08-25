#pragma once

#include <chrono>
#include <iostream>

namespace OSE
{
	using namespace std::chrono;

	struct TimeStep
	{
		friend class Timer;

		inline TimeStep() : m_Duration{ duration<double>::zero() } {}
		inline TimeStep(nanoseconds nanoseconds) : m_Duration{ duration_cast<duration<double>>(nanoseconds) } {}
		inline TimeStep(milliseconds milliseconds) : m_Duration{ duration_cast<duration<double>>(milliseconds) } {};
		inline TimeStep(double seconds) : m_Duration{ seconds } {};
		inline TimeStep(duration<double> duration) : m_Duration{ duration } {};

		inline double Seconds() const { return m_Duration.count(); }
		inline double Milliseconds() const { return m_Duration.count() * 1000.0; }

	private:
		std::chrono::duration<double> m_Duration;
	};
}
