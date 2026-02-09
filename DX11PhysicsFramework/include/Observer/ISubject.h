#pragma once
#include <Observer/IObserver.h>

class ISubject
{
public:
    virtual void RegisterObserver(IObserver* observer) = 0;
    virtual void RemoveObserver(IObserver* observer) = 0;
    virtual void NotifyObservers() = 0;
    virtual ~ISubject() = default;
};
