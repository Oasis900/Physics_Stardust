#pragma once
#include <Physics/Force.h>
#include <Physics/Gravity.h>
#include <Interface/IUpdateable.h>

static constexpr float DAMPENING = 0.99f;

class Motion final : public Force, public IUpdateable
{
    Vector3 velocity_;
    Vector3 acceleration_;
    Vector3 position_;
    Gravity* gravity_comp_ = nullptr;
    
public:
    Motion(CTransform* transform, Gravity* gravity) : Force(transform), position_(transform->GetPosition()), gravity_comp_(gravity) {}
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
    void Update(const float& dt) override;
    //--------------------------------------------------//
    void MyAttempt(const float& dt);
    void SemiImplicitEuler(const float& dt);
    void StormerVerlet(const float& dt);
    void VelocityVerlet(const float& dt);
    //--------------------------------------------------//
    ~Motion() override;
};
