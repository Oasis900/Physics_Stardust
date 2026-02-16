#include <Components/CRigidBody.h>
#include <Objects/GameObject.h>
#include <Core/Debug.h>

void CRigidBody::ApplyImpulse(const Vector3& impulse, const float& dt) const
{
    const Vector3 force = impulse * dt * restitution/GetInverseMass();
    
    GetMotion()->AddForce(force);
}

void CRigidBody::Update(const float& dt)
{
    Vector3 collision_normal = GetTransform()->GetPosition() - GetGameObject()->GetTransform()->GetPosition();
    const float depth = GetCollider()->GetRadius() + GetGameObject()->GetPhysics()->GetCollider()->GetRadius() - (GetGameObject()->GetTransform()->GetPosition() - GetTransform()->GetPosition()).Magnitude();
    collision_normal.Normalize();

    const Vector3 relative_velocity = GetMotion()->GetVelocity() - GetGameObject()->GetPhysics()->GetMotion()->GetVelocity();
    
    if (GetCollider()->CollidesWith(*GetGameObject()->GetPhysics()->GetCollider()) && collision_normal * relative_velocity <= 0.0f)
    {
        const float vj = -1E1 * collision_normal * relative_velocity;
        const float j = vj / (GetInverseMass() * GetGameObject()->GetPhysics()->GetInverseMass());
        
        Debug::DebugPrintF("\n Objects have collided");

        const float System_Mass = GetMass() + GetGameObject()->GetPhysics()->GetMass();
        
        GetTransform()->SetPosition(collision_normal * depth * (1 - (GetMass()/System_Mass)));
        GetGameObject()->GetTransform()->SetPosition(-collision_normal * depth * (1 - (GetGameObject()->GetPhysics()->GetMass()/System_Mass)));
        
        if (GetMotion()->GetVelocity().Magnitude() > tol)
        {
            ApplyImpulse(GetInverseMass() * j * collision_normal, dt);
        }
    }
    
    GetMotion()->Update(dt);
}
