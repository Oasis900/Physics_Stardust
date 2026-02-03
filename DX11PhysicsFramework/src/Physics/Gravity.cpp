#include <Core/constants.h>
#include <Physics/Gravity.h>
#include <Objects/GameObject.h>

Vector3 Gravity::CalculateGravity()
{
    if (GetTransform()->GetObjects().size() == 0) {return {0, 0, 0};}
    
    Vector3 combined_force;

    for (auto element : GetTransform()->GetObjects())
    {
        Vector3 distance = GetTransform()->GetPosition() - element->GetTransform()->GetPosition();
        if (distance.Magnitude() <= 0) { continue; }
        
        float gravity_x = static_cast<float>(k_G) * (GetInverseMass() * element->GetPhysics()->GetMass()) / (distance.x * distance.x);
        float gravity_y = static_cast<float>(k_G) * (GetInverseMass() * element->GetPhysics()->GetMass()) / (distance.y * distance.y);
        float gravity_z = static_cast<float>(k_G) * (GetInverseMass() * element->GetPhysics()->GetMass()) / (distance.z * distance.z);

        Vector3 gravity = Vector3(gravity_x, gravity_y, gravity_z);
        combined_force -= distance;
        combined_force += gravity;
    }
    
    combined_force.Normalize();
    
    SetNetForce(combined_force);
    
    return GetNetForce();
}
