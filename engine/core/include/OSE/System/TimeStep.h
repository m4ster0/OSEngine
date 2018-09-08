#pragma once

#include <chrono>
#include <iostream>

namespace OSE
{

	struct TimeStep
	{
		friend class Timer;

        using duration = std::chrono::duration<double>; //seconds

		inline TimeStep() : m_Duration{ 0 } {}
		inline TimeStep(double seconds) : m_Duration{ seconds } {};
		inline TimeStep(duration duration) : m_Duration{ duration.count() } {};

		inline double Seconds() const { return m_Duration.count(); }
		inline double Milliseconds() const { return m_Duration.count() * 1000.0; }

	private:
		std::chrono::duration<double> m_Duration;
	};
}
