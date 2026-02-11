#include <cmath>
#include <Core/constants.h>
#include <Physics/Gravity.h>
#include <Objects/GameObject.h>

Vector3 Gravity::CalculateGravity()
{
    Vector3 direction =  object_->GetTransform()->GetPosition() - GetTransform()->GetPosition();
    //if (direction.Magnitude() > 40.0f) {return {0,0,0};}
    float distance = sqrt(direction.Magnitude());
    direction.Normalize();
    
    float gravity_magnitude = static_cast<float>(k_G) * (GetMass() * object_->GetPhysics()->GetMass()) / distance;
    
    Vector3 gravity = direction * gravity_magnitude;
    
    return gravity;
}
