#pragma once
#include "../Components/CTransform.h"
#include "../Interface/IUpdateable.h"

class Motion : IUpdateable
{
    Vector3 velocity_;
    Vector3 acceleration_;
    Vector3 position_;
    CTransform* transform_ = nullptr;
    
public:
    Motion(CTransform* transform);
    //--------------------------------------------------//
    Vector3 GetVelocity() const {return velocity_;}
    void SetVelocity(const Vector3& velocity) {velocity_ = velocity;}
    //--------------------------------------------------//
    Vector3 GetAcceleration() const {return acceleration_;}
    void SetAcceleration(const Vector3& acceleration) {acceleration_ += acceleration;}
    void IncrementAcceleration() {acceleration_ *= 1.1f;}
    void DecrementAcceleration() {acceleration_ *= -1.1f;}
    void ResetAcceleration() {acceleration_ = Vector3(0.0f, 0.0f, 0.0f);}
    //--------------------------------------------------//
    void Update(const float& dt) final;
    //--------------------------------------------------//
    ~Motion();
};
