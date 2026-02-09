#include <Components/CPhysics.h>

/*void CPhysics::Update(const float& dt)
{
    if (motion_) motion_->Update(dt);
}*/

CPhysics::~CPhysics()
{
    if (motion_) {delete motion_; motion_ = nullptr;}
    if (gravity_) {delete gravity_; gravity_ = nullptr;}
    if (transform_) {transform_ = nullptr;}
    if (collider_) {delete collider_; collider_ = nullptr;}
    if (object_) {object_ = nullptr;}
}
