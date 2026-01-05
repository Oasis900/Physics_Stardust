#pragma once
#include <chrono>
#include <vector>

class Timer
{
    std::chrono::steady_clock::time_point last_frame_;
    
public:
    Timer();
    float GetDeltaTime();
    void TimeTick();
};
