#include "Timer.h"
using std::chrono::duration;

Timer::Timer()
{
    delta_time_ = duration<float>(steady_clock::now() - last_frame_).count();
}

float Timer::GetDeltaTime()
{
    return delta_time_;
}

void Timer::TimeTick()
{
    last_frame_ = steady_clock::now();
}

Timer::~Timer() {}
