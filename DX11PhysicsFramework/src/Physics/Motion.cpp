#include <Physics/Motion.h>

void Motion::Update(const float& dt)
{
    if (GetMass() <= 0.0f) { return; }

    assert(dt > 0.0f);
    
    acceleration_ += GetNetForce() / GetMass();
    acceleration_ += gravity_comp_->CalculateGravity();
    acceleration_ *= dt;
    
    velocity_ += acceleration_ * dt * 0.5f;
    position_ += velocity_ * dt;
    position_ *= powf(dampening_, dt);
    
    GetTransform()->SetPosition(position_);

    SetNetForce(Vector3(0.0f, 0.0f, 0.0f));
    acceleration_ = Vector3(0.0f, 0.0f, 0.0f);
}

Motion::~Motion()
{
    if (gravity_comp_) {gravity_comp_ = nullptr;}
}
