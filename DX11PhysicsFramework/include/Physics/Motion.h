#pragma once
#include <Physics/Force.h>
#include <Physics/Gravity.h>
#include <Interface/IUpdateable.h>

class Motion final : public Force, public IUpdateable
{
    Vector3 velocity_;
    Vector3 acceleration_;
    Vector3 position_;
    const float dampening_ = 0.99f;
    Gravity* gravity_comp_ = nullptr;
    
public:
    Motion(CTransform* transform, Gravity* gravity) : Force(transform)
    {
        gravity_comp_ = gravity;
        position_ = transform->GetPosition();
    }
    //--------------------------------------------------//
    Motion(const Motion& other) = delete;
    Motion& operator=(const Motion&) = delete;
    Motion(Motion&&) = delete;
    Motion& operator=(const Motion&&) = delete;
    //--------------------------------------------------//
    Vector3 GetVelocity() const {return velocity_;}
    //--------------------------------------------------//
    Vector3 GetAcceleration() const {return acceleration_;}
    //--------------------------------------------------//
    void Update(const float& dt) final;
    //--------------------------------------------------//
    void MyAttempt(const float& dt);
    void SemiImplicitEuler(const float& dt);
    void StormerVerlet(const float& dt);
    void VelocityVerlet(const float& dt);
    //--------------------------------------------------//
    ~Motion() override;
};
