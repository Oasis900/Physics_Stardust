#pragma once
#include <Physics/Force.h>
#include <Physics/Gravity.h>
#include <Interface/IUpdateable.h>

class Motion : public Force, public IUpdateable
{
    Vector3 velocity_;
    Vector3 acceleration_;
    Vector3 position_;
    Gravity* gravity_ = nullptr;
    
public:
    Motion(CTransform* transform, const float& mass);
    //--------------------------------------------------//
    Motion(const Motion& other) = delete;
    Motion& operator=(const Motion&) = delete;
    Motion(Motion&&) = delete;
    Motion& operator=(const Motion&&) = delete;
    //--------------------------------------------------//
    Vector3 GetVelocity() const {return velocity_;}
    //void SetVelocity(const Vector3& velocity) {velocity_ = velocity;}
    //--------------------------------------------------//
    Vector3 GetAcceleration() const {return acceleration_;}
    //void SetAcceleration(const Vector3& acceleration) {acceleration_ = acceleration;}
    //--------------------------------------------------//
    void Update(const float& dt) final;
    //--------------------------------------------------//
    ~Motion() override;
};
