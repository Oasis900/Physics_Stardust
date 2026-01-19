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
    float distance = Vector3(0,0,0).Magnitude() - GetTransform()->GetPosition().Magnitude();
    
    float gravity = G_CONSTANT * (GetMass() * GetMass()) / (distance * distance);
    
    Vector3 force = Vector3(gravity * GetMass(), gravity * GetMass(), gravity * GetMass());
    
    SetNetForce(force);
    
    return GetNetForce();
}

Gravity::~Gravity()
{
    
}
