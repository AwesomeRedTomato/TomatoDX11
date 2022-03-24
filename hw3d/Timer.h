#pragma once

using namespace std::chrono;
class Timer
{
	SINGLETON(Timer);
public:
	float Mark();
	float Peek();
private:
	steady_clock::time_point last;
};