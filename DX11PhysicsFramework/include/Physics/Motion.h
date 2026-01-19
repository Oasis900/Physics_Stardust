#pragma once
#include <Physics/Force.h>
#include <Physics/Gravity.h>
#include <Interface/IUpdateable.h>

constexpr float TIME = 1.0f/60.0f;

class Motion : public Force, public IUpdateable
{
    Vector3 velocity_;
    Vector3 acceleration_;
    Vector3 position_;
    const float dampening_ = 0.899f;
    Gravity* gravity_comp_ = nullptr;
    
public:
    Motion(CTransform* transform, const float& mass, Gravity* gravity) : Force(transform, mass)
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
    //void SetVelocity(const Vector3& velocity) {velocity_ = velocity;}
    //--------------------------------------------------//
    Vector3 GetAcceleration() const {return acceleration_;}
    //void SetAcceleration(const Vector3& acceleration) {acceleration_ = acceleration;}
    //--------------------------------------------------//
    void Update(const float& dt) final;
    //--------------------------------------------------//
    void MyAttempt(const float& dt);
    void SemiImplicitEuler(const float& dt);
    void StormerVerlet(const float& dt);
    void VelocityVerlet(const float& dt);
    Vector3 RungeKuttaK1(const float& dt);
    Vector3 RungeKuttaK2(const float& dt);
    Vector3 RungeKuttaK3(const float& dt);
    void RungeKuttaK4(const float& dt);
    //--------------------------------------------------//
    ~Motion() override;
};
