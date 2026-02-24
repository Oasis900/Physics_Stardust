#include <cmath>
#include <Physics/Gravity.h>
#include <Objects/GameObject.h>

Vector3 Gravity::CalculateGravity() const
{
    if (!is_gravity_enabled_)
    {
        return {0,0,0};
    }
    
    Vector3 direction =  GetGameObject()->GetTransform()->GetPosition() - GetTransform()->GetPosition();
    if (abs(direction.Magnitude()) > 100.0f) { return {0,0,0};}
    const float distance = direction.Magnitude();
    direction.Normalize();
    
    const float gravity_magnitude = static_cast<float>(k_G) * (GetMass() * GetGameObject()->GetPhysics()->GetMass()) / pow(distance, 2);
    
    Vector3 gravity = direction * gravity_magnitude;
    gravity /= GetMass();
    
    return gravity;
}

void Gravity::FlipSwitch()
{
    if (is_gravity_enabled_)
    {
        is_gravity_enabled_ = false;
    }
    else
    {
        is_gravity_enabled_ = true;
    }
}
