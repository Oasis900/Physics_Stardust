#pragma once
#include "../Components/CTransform.h"
#include "../Interface/IUpdateable.h"

class Velocity
{
    Vector3 velocity_;
    Vector3 acceleration_;
    Vector3 position_;
    
public:
    //--------------------------------------------------//
    Vector3 GetVelocity() const {return velocity_;}
    void SetVelocity(const Vector3& velocity) {velocity_ = velocity;}
    //--------------------------------------------------//
    void Update(float dt, CTransform* transform);
    //--------------------------------------------------//
};
