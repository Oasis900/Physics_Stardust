#include <Physics/Gravity.h>

Vector3 Gravity::CalculateGravity() const
{
    Vector3 gravity = Vector3(0,0,0);
    gravity.y = -earth_gravity_ * GetMass();
    return gravity;
}
