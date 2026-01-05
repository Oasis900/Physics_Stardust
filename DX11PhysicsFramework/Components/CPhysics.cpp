#include "CPhysics.h"

CPhysics::CPhysics(CTransform* transform)
{
    motion_ = new Motion(transform);
}

void CPhysics::Update(const float& dt)
{
    if (motion_) motion_->Update(dt);
}

CPhysics::~CPhysics()
{
    delete motion_; motion_ = nullptr;
}
