#include <Physics/Drag.h>
#include <Objects/GameObject.h>
#include <Core/constants.h>

Vector3 Drag::CalculateDrag(const Vector3& velocity) const 
{
    Vector3 direction = gravity_comp_->CalculateGravity();
    if (abs(direction.Magnitude()) > 10.0f) {return {0,0,0};}
    direction.Reverse();
    direction.Normalize();

    const float drag_magnitude = sphere_co_efficient * static_cast<float>(combined_Density) * (pow(velocity.Magnitude(), 2) / 2);

    Vector3 drag = direction * drag_magnitude;
   
    return drag;
}
