#pragma once
#include <Physics/Force.h>

class Gravity final : public Force
{
    bool is_gravity_enabled_;
public:
    explicit Gravity(CTransform* transform) : Force(transform) { is_gravity_enabled_ = true; }
    //--------------------------------------------------//
    Gravity(const Gravity& other) = delete;
    Gravity& operator=(const Gravity&) = delete;
    Gravity(Gravity&&) = delete;
    Gravity& operator=(const Gravity&&) = delete;
    //--------------------------------------------------//
    Vector3 CalculateGravity() const;
    //--------------------------------------------------//
    void FlipSwitch();
    //--------------------------------------------------//
    ~Gravity() override = default;
};
