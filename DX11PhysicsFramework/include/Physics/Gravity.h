#pragma once
#include <Physics/Force.h>

class Gravity : public Force
{
    const float earth_gravity_ = 9.81f;
public:
    Gravity(CTransform* transform, const float& mass) : Force(transform, mass) {}
    Vector3 CalculateGravity() const;
};
