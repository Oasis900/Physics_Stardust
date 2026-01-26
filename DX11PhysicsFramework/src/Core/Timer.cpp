#include <Core/Timer.h>
using std::chrono::steady_clock;
using std::chrono::duration;

float Timer::GetDeltaTime()
{
    float frame_time = duration<float>(steady_clock::now() - last_frame_).count();

    frame_time = std::min<float>(frame_time, MAX_FRAME_TIME);

    TimeTick();

    return frame_time;
}

void Timer::TimeTick()
{
    last_frame_ = steady_clock::now();
}
