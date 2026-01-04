#pragma once
#include <chrono>

class Timer
{
    std::chrono::steady_clock::time_point last_frame_;
    
public:
    Timer();
    float GetDeltaTime() const;
    void TimeTick();
};
