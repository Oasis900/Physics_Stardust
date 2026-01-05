#include "Timer.h"
using std::chrono::steady_clock;
using std::chrono::duration;
using std::min;

Timer::Timer()
{
    TimeTick();
}

float Timer::GetDeltaTime()
{
    float frame_time = duration<float>(steady_clock::now() - last_frame_).count();
    
    if (frame_time > 0.25f) frame_time = 0.25f;
    
    TimeTick();
    
    return frame_time;
}

void Timer::TimeTick()
{
    last_frame_ = steady_clock::now();
}
