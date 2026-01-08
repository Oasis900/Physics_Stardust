#include <Components/CPhysics.h>

CPhysics::CPhysics(CTransform* transform, const float& mass)
{
    motion_ = new Motion(transform, mass);
}

void CPhysics::Update(const float& dt)
{
    if (motion_) motion_->Update(dt);
}

CPhysics::~CPhysics()
{
    delete motion_; motion_ = nullptr;
}
