#include <Physics/Motion.h>

void Motion::Update(const float& dt)
{
    if (GetMass() <= 0.0f) { return; }

    assert(dt > 0.0f);
    
    if (gravity_comp_->GetToggleGravity()) { acceleration_ += gravity_comp_->CalculateGravity(); }
    
    acceleration_ += GetNetForce() / GetMass();
    acceleration_ *= dt;

    RungeKuttaK4(dt);
    
    GetTransform()->SetPosition(position_);

    SetNetForce(Vector3(0.0f, 0.0f, 0.0f));
    acceleration_ = Vector3(0.0f, 0.0f, 0.0f);
}

void Motion::MyAttempt(const float& dt)
{
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
    position_ *= powf(dampening_, dt);
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

Vector3 Motion::RungeKuttaK1(const float& dt)
{
    velocity_ += acceleration_ * dt;
    Vector3 position = velocity_ * dt;
    return position;
}

Vector3 Motion::RungeKuttaK2(const float& dt)
{
    Vector3 K1 = RungeKuttaK1(dt);
    Vector3 position = velocity_ * (dt / 2) + (K1/2) * dt;
    return position;
}

Vector3 Motion::RungeKuttaK3(const float& dt)
{
    Vector3 K2 = RungeKuttaK2(dt);
    Vector3 position = velocity_ * (dt / 2) + (K2/2) * dt;
    return position;
}

void Motion::RungeKuttaK4(const float& dt)
{
    Vector3 K3 = RungeKuttaK3(dt);
    position_ += velocity_ * dt + K3 * dt;
}


Motion::~Motion()
{
    if (gravity_comp_) {gravity_comp_ = nullptr;}
}
