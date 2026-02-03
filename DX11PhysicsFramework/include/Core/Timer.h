#pragma once
#include <chrono>

static constexpr float MAX_FRAME_TIME = 0.25f;

class Timer
{
    std::chrono::steady_clock::time_point last_frame_;
    
public:
    float GetDeltaTime();
    void TimeTick();
};
