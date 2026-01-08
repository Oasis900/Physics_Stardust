#include <Physics/Motion.h>

Motion::Motion(CTransform* transform, const float& mass) : Force(transform, mass)
{
    gravity_ = new Gravity(transform, mass);
    position_ = transform_->GetPosition();
}

void Motion::Update(const float& dt)
{
    acceleration_ += net_force_ / mass_ * dt;
    
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
    
    transform_->SetPosition(position_);

    ResetForce();
}

void Motion::ResetForce()
{
    net_force_ = Vector3(0.0f, 0.0f, 0.0f);
    acceleration_ = Vector3(0.0f, 0.0f, 0.0f);
}

Motion::~Motion()
{
    delete gravity_; gravity_ = nullptr;
}
