#include "SolarSystemTimer.h"

Timer *Timer::m_Instance = 0;

Timer::Timer()
{
	ResetTimer();
}

Timer *Timer::GetInstance()
{
	if(!m_Instance)
		m_Instance = new Timer();
	return m_Instance;
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