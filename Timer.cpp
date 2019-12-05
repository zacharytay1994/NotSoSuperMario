#include "Timer.h"


Timer::Timer()
	:
	duration(0)
{
}

Timer::~Timer()
{
}

void Timer::StartTimer(std::clock_t st)
{
	startTime = st;
}

void Timer::StopTimer()
{
	isTimerStopped = true;
}

void Timer::ContinueTimer()
{
	isTimerStopped = false;
}

void Timer::Update()
{
	if (!v)
	{
		pausedDuration += tempPausedDuration;
		v = true;
	}
	if (!isTimerStopped)
	{
		
		endTime = clock();
		clockTicksTaken = endTime - startTime - pausedDuration;
		duration = clockTicksTaken / (double)CLOCKS_PER_SEC;

	}
}

void Timer::PausedDuration()
{
	if (isTimerStopped)
	{
		if (v)
		{
			pausedStartTime = clock();
			v = false;
		}
		pausedEndTime = clock();
		tempPausedDuration = pausedEndTime - pausedStartTime;
		
	}
}

double Timer::Duration()
{
	return duration;
}


