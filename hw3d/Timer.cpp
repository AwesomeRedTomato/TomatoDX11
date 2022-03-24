#include "pch.h"
#include "Timer.h"

float Timer::Mark() 
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float Timer::Peek()
{
	return duration<float>(steady_clock::now() - last).count();
}
