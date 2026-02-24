#pragma once
#include <Physics/Force.h>

class IUpdateable;
class Gravity;
class Drag;

static constexpr float DAMPENING = 0.99f;

class Motion final : public Force, public IUpdateable
{
    Vector3 velocity_ = {0,0,0};
    Vector3 acceleration_ = {0,0,0};
    Vector3 position_ = {0,0,0};
    Gravity* gravity_comp_ = nullptr;
    Drag* drag_comp_ = nullptr;
    
public:
    Motion(CTransform* transform, Gravity* gravity, Drag* drag) : Force(transform), position_(transform->GetPosition()), gravity_comp_(gravity), drag_comp_(drag) {}
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

inline Motion::~Motion()
{
    if (gravity_comp_) {gravity_comp_ = nullptr;}
    if (drag_comp_) {drag_comp_ = nullptr;}
}
