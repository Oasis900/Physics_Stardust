#include "Motion.h"

Motion::Motion(CTransform* transform)
{
    transform_ = transform;
    position_ = transform_->GetPosition();
}

void Motion::Update(const float& dt)
{
    if (acceleration_.x == 0.0f && acceleration_.y == 0.0f && acceleration_.z == 0.0f) return;
    velocity_ += acceleration_ * dt;
    position_ += velocity_ * dt;
    transform_->SetPosition(position_);
}

Motion::~Motion()
{
    transform_ = nullptr;
}
