#include <Components/CPhysics.h>

CPhysics::~CPhysics()
{
    if (gravity_) {delete gravity_; gravity_ = nullptr;}
    if (motion_) {delete motion_; motion_ = nullptr;}
    if (transform_) {transform_ = nullptr;}
    if (collider_) {delete collider_; collider_ = nullptr;}
    if (object_) {object_ = nullptr;}
}
