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
    if (!toggle_gravity_) {return {0,0,0};}

    SetNetForce(Vector3(0,-EARTH_GRAVITY * GetMass(),0));
    
    return GetNetForce();
}
