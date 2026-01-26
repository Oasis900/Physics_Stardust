#include <Physics/Gravity.h>

/*void Gravity::ToggleGravity()
{
    if (!toggle_gravity_)
    {
        toggle_gravity_ = true;
    }
    else
    {
        toggle_gravity_ = false;
    }
}*/

Vector3 Gravity::CalculateGravity()
{
    Vector3 distance = GetTransform()->GetPosition() - Vector3(0,0,0);
    
    float gravity_x = G_CONSTANT * (GetInverseMass() * 0.9f) / (distance.x * distance.x);
    float gravity_y = G_CONSTANT * (GetInverseMass() * 0.9f) / (distance.y * distance.y);
    float gravity_z = G_CONSTANT * (GetInverseMass() * 0.9f) / (distance.z * distance.z);

    Vector3 gravity = Vector3(gravity_x, gravity_y, gravity_z);

    gravity.Normalize();
    
    Vector3 force = gravity - GetTransform()->GetPosition();
    
    SetNetForce(force);
    
    return GetNetForce();
}

Gravity::~Gravity()
{
    
}
