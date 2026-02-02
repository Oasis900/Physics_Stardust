#include <Physics/Gravity.h>
#include <Objects/GameObject.h>

Vector3 Gravity::CalculateGravity()
{
    if (GetTransform()->GetObjects().size() == 0) {return {0, 0, 0};}
    
    float combined_x = 0, combined_y = 0, combined_z = 0;

    for (auto element : GetTransform()->GetObjects())
    {
        Vector3 distance = GetTransform()->GetPosition() - element->GetTransform()->GetPosition();
        if (distance.Magnitude() <= 0) { continue; }
        
        float gravity_x = G_CONSTANT * (GetMass() * element->GetPhysics()->GetGravity()->GetMass()) / (distance.x * distance.x);
        float gravity_y = G_CONSTANT * (GetMass() * element->GetPhysics()->GetGravity()->GetMass()) / (distance.y * distance.y);
        float gravity_z = G_CONSTANT * (GetMass() * element->GetPhysics()->GetGravity()->GetMass()) / (distance.z * distance.z);

        combined_x += gravity_x;
        combined_y += gravity_y;
        combined_z += gravity_z;
    }

    Vector3 gravity = Vector3(combined_x, combined_y, combined_z);

    gravity.Normalize();
    
    Vector3 force = gravity - GetTransform()->GetPosition();

    if (gravity.Magnitude() <= 0) {force.Normalize();}
    
    SetNetForce(force);
    
    return GetNetForce();
}
