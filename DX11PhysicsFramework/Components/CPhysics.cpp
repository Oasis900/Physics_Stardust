#include "CPhysics.h"

CPhysics::CPhysics()
{
    velocity_ = new Velocity();
}

void CPhysics::Update(const float& dt)
{
    if (velocity_) velocity_->Update(dt, transform_);
}

CPhysics::~CPhysics()
{
    delete velocity_; velocity_ = nullptr;
    transform_ = nullptr;
}
