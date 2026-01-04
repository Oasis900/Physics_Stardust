#pragma once
#include "../Physics/Velocity.h"

class CPhysics : public IUpdateable
{
    Velocity* velocity_ = nullptr;
    CTransform* transform_ = nullptr;
    
public:
    CPhysics();
    //--------------------------------------------------//
    void SetTransform(CTransform* transform) {transform_ = transform;};
    Velocity* GetVelocity() const { return velocity_; }
    //--------------------------------------------------//
    //void ActivateModule();
    //--------------------------------------------------//
    void Update(const float& dt) final;
    //--------------------------------------------------//
    ~CPhysics();
    
};
