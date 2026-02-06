#pragma once
#include <Physics/Force.h>

// TODO (Gravity) [12/01/26] : Review class when attempting General Relativity

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
    Vector3 CalculateGravity(const GameObject* other);
    //--------------------------------------------------//
    ~Gravity() override = default;
};
