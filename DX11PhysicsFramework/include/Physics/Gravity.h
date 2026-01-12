#pragma once
#include <Physics/Force.h>

// TODO (Gravity) [12/01/26] : Review class when attempting General Relativity

constexpr float EARTH_GRAVITY = 9.80665f;

class Gravity : public Force
{
    bool toggle_gravity_;
public:
    Gravity(CTransform* transform, const float& mass) : Force(transform, mass) {toggle_gravity_ = false;}
    //--------------------------------------------------//
    bool GetToggleGravity() const {return toggle_gravity_;}
    //--------------------------------------------------//
    void ToggleGravity();
    //--------------------------------------------------//
    Vector3 CalculateGravity();
};
