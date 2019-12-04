#pragma once
#include <ctime>

class Timer
{
	private:
		double duration = 0;
		double pausedDuration = 0;
		double tempPausedDuration = 0;
		bool v = true;
		std::clock_t startTime;
		std::clock_t endTime;
		std::clock_t clockTicksTaken;
		std::clock_t pausedStartTime;
		std::clock_t pausedEndTime;
		std::clock_t pausedClockTicksTaken;
		bool isTimerStopped = false;

	public:
		Timer();
		~Timer();
		void Update();
		void StartTimer(std::clock_t st);
		void StopTimer();
		void ContinueTimer();
		void PausedDuration();
		double Duration();
		
};