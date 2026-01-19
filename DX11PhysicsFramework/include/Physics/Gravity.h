#pragma once
#include <Physics/Force.h>

// TODO (Gravity) [12/01/26] : Review class when attempting General Relativity

constexpr float G_CONSTANT = 0.000000000006743f;

class Gravity : public Force
{
    bool toggle_gravity_;
public:
    Gravity(CTransform* transform, const float& mass) : Force(transform, mass)
    {
        toggle_gravity_ = false;
    }
    //--------------------------------------------------//
    bool GetToggleGravity() const {return toggle_gravity_;}
    //--------------------------------------------------//
    void ToggleGravity();
    //--------------------------------------------------//
    Vector3 CalculateGravity();
    //--------------------------------------------------//
    ~Gravity() override;
};
