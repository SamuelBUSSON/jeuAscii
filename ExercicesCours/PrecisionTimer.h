#ifndef PRECISION_TIMER_H
#define PRECISION_TIMER_H
//-----------------------------------------------------------------------
//
//  Name: PrecisionTimer.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Windows timer class.
//
//        nb. this only uses the high performance timer. There is no
//        support for ancient computers. I know, I know, I should add
//        support, but hey, I have shares in AMD and Intel... Go upgrade ;o)
//
//-----------------------------------------------------------------------
#include <cassert>

class PrecisionTimer
{
private:

	LONGLONG  m_CurrentTime,
		m_LastTime,
		m_LastTimeInTimeElapsed,
		m_NextTime,
		m_StartTime,
		m_FrameTime,
		m_PerfCountFreq;

	double    m_TimeElapsed,
		m_LastTimeElapsed,
		m_TimeScale;

	double    m_NormalFPS;
	double    m_SlowFPS;

	bool      m_bStarted;

	//if true a call to TimeElapsed() will return 0 if the current
	//time elapsed is much smaller than the previous. Used to counter
	//the problems associated with the user using menus/resizing/moving
	//a window etc
	bool      m_bSmoothUpdates;

public:

	//ctors
	PrecisionTimer();
	PrecisionTimer(double fps);

	//whatdayaknow, this starts the timer
	void    Start();

	//determines if enough time has passed to move onto next frame
	inline bool    ReadyForNextFrame();

	//only use this after a call to the above.
	//double  GetTimeElapsed(){return m_TimeElapsed;}

	inline double  TimeElapsed();

	double  CurrentTime()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);

		return (m_CurrentTime - m_StartTime) * m_TimeScale;
	}

	bool    Started()const { return m_bStarted; }

	void    SmoothUpdatesOn() { m_bSmoothUpdates = true; }
	void    SmoothUpdatesOff() { m_bSmoothUpdates = false; }
};

#endif
