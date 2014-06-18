#include "profiling.h"
#include "timing.h"
#include <cassert>
#include <iostream>

void ProfileTimer::StartInvocation()
{
	m_startTime = Time::GetTime();
}

void ProfileTimer::StopInvocation()
{
	if(m_startTime == 0)
	{
		std::cout << "Error: StopInvocation called without matching start invocation" << std::endl;
		assert(m_startTime != 0);
	}
	
	m_numInvocations++;
	m_totalTime += (Time::GetTime() - m_startTime);
	m_startTime = 0;
}

double ProfileTimer::GetTimeAndReset(double dividend)
{
	dividend = (dividend == 0) ? m_numInvocations : dividend;
	double result = (m_totalTime == 0 && dividend == 0.0) ? 0.0 : (1000.0 * m_totalTime)/((double)dividend);
	m_totalTime = 0.0;
	m_numInvocations = 0;
	
	return result;
}

double ProfileTimer::DisplayAndReset(const std::string& message, double dividend, int displayedMessageLength)
{
	std::string whiteSpace = "";
	for(int i = message.length(); i < displayedMessageLength; i++)
	{
		whiteSpace += " ";
	}
	
	double time = GetTimeAndReset(dividend);
	std::cout << message << whiteSpace << time << " ms" << std::endl;
	return time;
}
