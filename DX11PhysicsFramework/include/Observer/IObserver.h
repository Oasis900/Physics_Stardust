#pragma once

class IObserver
{
public:
    virtual void Notification() = 0;
    virtual ~IObserver() = default;
};
