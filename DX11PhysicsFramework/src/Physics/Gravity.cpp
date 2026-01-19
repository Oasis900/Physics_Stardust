#include <Physics/Gravity.h>

void Gravity::ToggleGravity()
{
    if (!toggle_gravity_)
    {
        toggle_gravity_ = true;
    }
    else
    {
        toggle_gravity_ = false;
    }
}

Vector3 Gravity::CalculateGravity()
{
    SetNetForce(Vector3(0,-EARTH_GRAVITY * GetMass(),0));
    
    return GetNetForce();
}
