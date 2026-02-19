#pragma once
#include <Physics/Force.h>

class Gravity;

class Drag : public Force
{
    Gravity* gravity_comp_ = nullptr;

public:
    explicit Drag(CTransform* transform, Gravity* gravity) : Force(transform), gravity_comp_(gravity) {}
    //--------------------------------------------------//
    Drag(const Drag& other) = delete;
    Drag& operator=(const Drag&) = delete;
    Drag(Drag&&) = delete;
    Drag& operator=(const Drag&&) = delete;
    //--------------------------------------------------//
    Vector3 CalculateDrag(const Vector3& velocity) const;
    //--------------------------------------------------//
    ~Drag() override;
};

inline Drag::~Drag()
{
    gravity_comp_ = nullptr;
}

