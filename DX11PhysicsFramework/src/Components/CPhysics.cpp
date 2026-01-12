#include <Components/CPhysics.h>

CPhysics::CPhysics(CTransform* transform, const float& mass)
{
    gravity_ = new Gravity(transform, mass);
    motion_ = new Motion(transform, mass, gravity_);
}

void CPhysics::Update(const float& dt)
{
    if (motion_) motion_->Update(dt);
}

CPhysics::~CPhysics()
{
    if (motion_) {delete motion_; motion_ = nullptr;}
    if (gravity_) {delete gravity_; gravity_ = nullptr;}
}
