#ifndef TIMER_H_
#define TIMER_H_

#include <ctime>

using namespace std;

class Timer
{
private:
	static Timer *m_Instance;
    Timer();
	Timer(const Timer& timer);
	void operator=(const Timer& timer);
public:
	static Timer *GetInstance();

	//Resets the timer's reference time & lap time.
	void	ResetTimer();

	// Stops the timer at a certain time. (Calling this method more than once 
	// without resetting the timer sets the lap time at the last time this
	// method was called. )
	void	MarkLap();

	//Returns the time elapsed (in seconds) between the reset and the current time.
	float	GetTime() const;

	//Returns the time elapsed (in seconds) between the last reset time and the last lap time.
	float	GetLapTime() const;

protected:

	clock_t mo_ReferenceTime;
	clock_t mo_LapTime;

};

#endif //TIMER_H_