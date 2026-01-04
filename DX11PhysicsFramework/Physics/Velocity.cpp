#include "Velocity.h"

void Velocity::Update(const float dt, CTransform* transform)
{
    position_ = transform->GetPosition();
    position_ += velocity_ * dt;
    transform->SetPosition(position_);
}
