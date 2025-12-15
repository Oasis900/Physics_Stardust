#pragma once
#include <chrono>
using std::chrono::steady_clock;

class Timer
{
    float delta_time_;
    steady_clock::time_point last_frame_;
    
public:
    Timer();
    float GetDeltaTime();
    void TimeTick();
    ~Timer();
};
