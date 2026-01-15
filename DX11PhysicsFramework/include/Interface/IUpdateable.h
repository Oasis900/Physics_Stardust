#pragma once
#define INTERFACE_UPDATE_HPP

struct IUpdateable
{
    virtual void Update(const float& dt) = 0;
};