#pragma once

struct IUpdateable
{
    virtual void Update(const float& dt) = 0;
};
