#include <cmath>
#include <Physics/Gravity.h>
#include <Objects/GameObject.h>

Vector3 Gravity::CalculateGravity() const
{
    Vector3 direction =  GetGameObject()->GetTransform()->GetPosition() - GetTransform()->GetPosition();
    const float distance = sqrt(direction.Magnitude());
    direction.Normalize();
    
    const float gravity_magnitude = static_cast<float>(k_G) * (GetMass() * GetGameObject()->GetPhysics()->GetMass()) / distance;
    
    const Vector3 gravity = direction * gravity_magnitude;
    
    return gravity;
}
