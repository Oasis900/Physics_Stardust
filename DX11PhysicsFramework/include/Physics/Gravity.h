#pragma once
#include <vector>
#include <Physics/Force.h>

// TODO (Gravity) [12/01/26] : Review class when attempting General Relativity

constexpr float G_CONSTANT = 6.6743e-11f;

class Gravity : public Force
{
public:
    explicit Gravity(CTransform* transform) : Force(transform) {}
    //--------------------------------------------------//
    Gravity(const Gravity& other) = delete;
    Gravity& operator=(const Gravity&) = delete;
    Gravity(Gravity&&) = delete;
    Gravity& operator=(const Gravity&&) = delete;
    //--------------------------------------------------//
    Vector3 CalculateGravity();
    //--------------------------------------------------//
    ~Gravity() override = default;
};
