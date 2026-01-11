#include <Physics/Motion.h>

Motion::Motion(CTransform* transform, const float& mass) : Force(transform, mass)
{
    gravity_ = new Gravity(transform, mass);
    position_ = GetTransform()->GetPosition();
}

void Motion::Update(const float& dt)
{
    acceleration_ += GetNetForce() / GetMass() * dt;
    
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
    
    GetTransform()->SetPosition(position_);

    SetNetForce(Vector3(0.0f, 0.0f, 0.0f));
    acceleration_ = Vector3(0.0f, 0.0f, 0.0f);
}

Motion::~Motion()
{
    if (gravity_) {delete gravity_; gravity_ = nullptr;}
}
