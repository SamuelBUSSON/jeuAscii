#include "PrecisionTimer.h"

//---------------------- default constructor ------------------------------
//
//-------------------------------------------------------------------------
PrecisionTimer::PrecisionTimer() : m_NormalFPS(0.0),
m_SlowFPS(1.0),
m_TimeElapsed(0.0),
m_FrameTime(0),
m_LastTime(0),
m_LastTimeInTimeElapsed(0),
m_PerfCountFreq(0),
m_bStarted(false),
m_StartTime(0),
m_LastTimeElapsed(0.0),
m_bSmoothUpdates(false)
{
	//how many ticks per sec do we get
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_PerfCountFreq);

	m_TimeScale = 1.0 / m_PerfCountFreq;
}

//---------------------- constructor -------------------------------------
//
//  use to specify FPS
//
//-------------------------------------------------------------------------
PrecisionTimer::PrecisionTimer(double fps) : m_NormalFPS(fps),
m_SlowFPS(1.0),
m_TimeElapsed(0.0),
m_FrameTime(0),
m_LastTime(0),
m_LastTimeInTimeElapsed(0),
m_PerfCountFreq(0),
m_bStarted(false),
m_StartTime(0),
m_LastTimeElapsed(0.0),
m_bSmoothUpdates(false)
{
	//how many ticks per sec do we get
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_PerfCountFreq);

	m_TimeScale = 1.0 / m_PerfCountFreq;

	//calculate ticks per frame
	m_FrameTime = (LONGLONG)(m_PerfCountFreq / m_NormalFPS);
}

//------------------------Start()-----------------------------------------
//
//  call this immediately prior to game loop. Starts the timer (obviously!)
//
//--------------------------------------------------------------------------
void PrecisionTimer::Start()
{
	m_bStarted = true;

	m_TimeElapsed = 0.0;

	//get the time
	QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime);

	//keep a record of when the timer was started
	m_StartTime = m_LastTimeInTimeElapsed = m_LastTime;

	//update time to render next frame
	m_NextTime = m_LastTime + m_FrameTime;

	return;
}

//-------------------------ReadyForNextFrame()-------------------------------
//
//  returns true if it is time to move on to the next frame step. To be used if
//  FPS is set.
//
//----------------------------------------------------------------------------
inline bool PrecisionTimer::ReadyForNextFrame()
{
	assert(m_NormalFPS && "PrecisionTimer::ReadyForNextFrame<No FPS set in timer>");

	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);

	if (m_CurrentTime > m_NextTime)
	{
		m_TimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;
		m_LastTime = m_CurrentTime;

		//update time to render next frame
		m_NextTime = m_CurrentTime + m_FrameTime;

		return true;
	}

	return false;
}

//--------------------------- TimeElapsed --------------------------------
//
//  returns time elapsed since last call to this function.
//-------------------------------------------------------------------------
inline double PrecisionTimer::TimeElapsed()
{
	m_LastTimeElapsed = m_TimeElapsed;

	QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);

	m_TimeElapsed = (m_CurrentTime - m_LastTimeInTimeElapsed) * m_TimeScale;

	m_LastTimeInTimeElapsed = m_CurrentTime;

	const double Smoothness = 5.0;

	if (m_bSmoothUpdates)
	{
		if (m_TimeElapsed < (m_LastTimeElapsed * Smoothness))
		{
			return m_TimeElapsed;
		}

		else
		{
			return 0.0;
		}
	}

	else
	{
		return m_TimeElapsed;
	}
}