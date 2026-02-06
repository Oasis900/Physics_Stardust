#include <Physics/Motion.h>

void Motion::Update(const float& dt)
{
    if (GetMass() <= 0.0f) { return; }

    assert(dt > 0.0f);

    acceleration_ += gravity_comp_->CalculateGravity(GetTransform()->GetGameObject()) / GetMass();
    acceleration_ += GetNetForce() / GetMass();
    acceleration_ *= dt;

    VelocityVerlet(dt);
    
    GetTransform()->SetPosition(position_);

    SetNetForce(Vector3(0.0f, 0.0f, 0.0f));
    acceleration_ = Vector3(0.0f, 0.0f, 0.0f);
}

void Motion::MyAttempt(const float& dt)
{
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
    position_ *= powf(DAMPENING, dt);
}

void Motion::SemiImplicitEuler(const float& dt)
{
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
}

void Motion::StormerVerlet(const float& dt)
{
    Vector3 previous_pos = position_;
    position_ += position_ * 2 - previous_pos + acceleration_ * (dt * dt);
}

void Motion::VelocityVerlet(const float& dt)
{
    velocity_ = (velocity_ + acceleration_ + acceleration_ * dt) / 2 * dt;
    position_ += velocity_ * dt + acceleration_ * 0.5f * (dt * dt);
}

Motion::~Motion()
{
    if (gravity_comp_) {gravity_comp_ = nullptr;}
}
