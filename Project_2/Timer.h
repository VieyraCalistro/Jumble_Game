#pragma once
#include <ctime>
#include <conio.h>
class Timer
{

public:
	~Timer()
	{

	}

	unsigned int startTime;

	Timer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli) {}
	}

};

