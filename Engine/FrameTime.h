#pragma once
#include<chrono>

//a class to count the time between frame to frame
using namespace std::chrono;
class FrameTimer
{
public:
	FrameTimer();
	float Mark();
private:
	steady_clock::time_point last;
};