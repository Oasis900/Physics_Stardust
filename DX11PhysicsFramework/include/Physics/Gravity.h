#pragma once
#include <Physics/Force.h>

// TODO (Gravity) [12/01/26] : Review class when attempting General Relativity

constexpr float G_CONSTANT = 6.6743e-11f;

class Gravity : public Force
{
    //bool toggle_gravity_;
public:
    explicit Gravity(CTransform* transform) : Force(transform) {}
    //--------------------------------------------------//
    //bool GetToggleGravity() const {return toggle_gravity_;}
    //--------------------------------------------------//
    //void ToggleGravity();
    //--------------------------------------------------//
    Vector3 CalculateGravity();
    //--------------------------------------------------//
    ~Gravity() override;
};
