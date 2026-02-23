#pragma once
#include <Physics/Force.h>

namespace Colliders
{
    class Collider;
}

class Drag : public Force
{
    Colliders::Collider* collider_ = nullptr;

public:
    explicit Drag(CTransform* transform) : Force(transform) {}
    //--------------------------------------------------//
    Drag(const Drag& other) = delete;
    Drag& operator=(const Drag&) = delete;
    Drag(Drag&&) = delete;
    Drag& operator=(const Drag&&) = delete;
    //--------------------------------------------------//
    Vector3 CalculateDrag(const Vector3& velocity) const;
    //--------------------------------------------------//
    void SetCollider(Colliders::Collider* collider) {collider_ = collider;}
    //--------------------------------------------------//
    ~Drag() override;
};

inline Drag::~Drag()
{
    collider_ = nullptr;
}

