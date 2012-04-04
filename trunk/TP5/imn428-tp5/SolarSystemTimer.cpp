#include "SolarSystemTimer.h"

Timer::Timer()
{
	ResetTimer();
}

void Timer::ResetTimer()
{
	mo_ReferenceTime = clock();
	mo_LapTime = clock();
}

void Timer::MarkLap()
{
	mo_LapTime = clock();
}

float Timer::GetTime() const
{
	return (clock() - mo_ReferenceTime) / float(CLOCKS_PER_SEC);
}

float Timer::GetLapTime() const
{
	return ( mo_LapTime - mo_ReferenceTime ) / float(CLOCKS_PER_SEC);
}