#include <Components/CPhysics.h>

CPhysics::CPhysics(CTransform* transform)
{
    gravity_ = new Gravity(transform);
    motion_ = new Motion(transform, gravity_);
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
