#include "Timer.h"
using std::chrono::steady_clock;
using std::chrono::duration;
using std::min;

Timer::Timer()
{
    TimeTick();
}

float Timer::GetDeltaTime() const 
{
    float dt = duration<float>(steady_clock::now() - last_frame_).count();

    //if (static_cast<bool>(min(dt, 0.25f))) dt = 0.25f;
    
    return dt;
}

void Timer::TimeTick()
{
    last_frame_ = steady_clock::now();
}
