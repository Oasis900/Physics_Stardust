#pragma once
#include <Physics/Force.h>

class Gravity final : public Force
{
public:
    explicit Gravity(CTransform* transform) : Force(transform) {}
    //--------------------------------------------------//
    Gravity(const Gravity& other) = delete;
    Gravity& operator=(const Gravity&) = delete;
    Gravity(Gravity&&) = delete;
    Gravity& operator=(const Gravity&&) = delete;
    //--------------------------------------------------//
    Vector3 CalculateGravity() const;
    //--------------------------------------------------//
    ~Gravity() override = default;
};
