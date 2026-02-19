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
    if (GetCollider()->CollidesWith(*GetGameObject()->GetPhysics()->GetCollider()))
    {
        const Vector3 objA_pos = GetTransform()->GetPosition(), objB_pos = GetGameObject()->GetTransform()->GetPosition();
        const Vector3 objA_velocity = GetMotion()->GetVelocity(), objB_velocity = GetGameObject()->GetPhysics()->GetMotion()->GetVelocity();
        const float objA_radius = GetCollider()->GetRadius(), objB_radius = GetGameObject()->GetPhysics()->GetCollider()->GetRadius();
        
        Vector3 collision_normal = objA_pos - objB_pos;
        const float depth = objA_radius + objB_radius - (objA_pos - objB_pos).Magnitude();
        collision_normal.Normalize();

        const Vector3 relative_velocity = objA_velocity - objB_velocity;

        if (collision_normal * relative_velocity <= 0.0f)
        {
            const float objA_I_mass = GetInverseMass(), objB_I_mass = GetGameObject()->GetPhysics()->GetInverseMass();
            
            const float vj = -1E1 * collision_normal * relative_velocity;
            const float j = vj / (objA_I_mass * objB_I_mass);
        
            Debug::DebugPrintF("\n Objects have collided");

            const float objA_mass = GetMass(), objB_mass = GetGameObject()->GetPhysics()->GetMass();
            const float system_mass = objA_mass + objB_mass;
        
            GetTransform()->SetPosition(collision_normal * depth * (1 - objA_mass/system_mass));
            GetGameObject()->GetTransform()->SetPosition(-collision_normal * depth * (1 - objB_mass/system_mass));
        
            if (objA_velocity.Magnitude() > tol)
            {
                ApplyImpulse(objA_I_mass * j * collision_normal, dt);
            }
        }
    }
    
    GetMotion()->Update(dt);
}
