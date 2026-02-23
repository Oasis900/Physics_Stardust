#include <Physics/Drag.h>
#include <Objects/GameObject.h>
#include <Core/constants.h>

Vector3 Drag::CalculateDrag(const Vector3& velocity) const 
{
    const Vector3 distance = GetGameObject()->GetTransform()->GetPosition() - GetTransform()->GetPosition();
    if (abs(distance.Magnitude()) > 10.0f) {return {0,0,0};}
    
    if (abs(velocity.Magnitude()) < tol) {return {0,0,0};}
    Vector3 direction = velocity;
    direction.Reverse();
    const float velocity_magnitude = direction.Magnitude() * 100;
    direction.Normalize();

    const float reference_area = M_PI * pow(collider_->GetRadius(), 2);

    const float drag_magnitude = static_cast<float>(relative_Density) * pow(velocity.Magnitude(), 2)
        * sphere_co_efficient * (reference_area / GetMass());

    Vector3 drag = direction * drag_magnitude * velocity_magnitude;
    drag /= GetMass();
   
    return drag;
}
