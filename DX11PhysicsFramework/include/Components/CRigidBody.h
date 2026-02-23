#pragma once
#include <Components/CPhysics.h>

constexpr float restitution = 1E-6; // Magical number, change for bouncy-iness

class CRigidBody : public CPhysics
{
    
public:
    explicit CRigidBody(CTransform* transform) : CPhysics(transform) {}
    //--------------------------------------------------//
    CRigidBody(const CRigidBody& other) = delete;
    CRigidBody& operator=(const CRigidBody&) = delete;
    CRigidBody(CRigidBody&&) = delete;
    CRigidBody& operator=(const CRigidBody&&) = delete;
    //--------------------------------------------------//
    void ApplyImpulse(const Vector3& impulse, const float& dt) const; 
    //--------------------------------------------------//
    void Update(const float& dt) override;
    //--------------------------------------------------//
    ~CRigidBody() override = default;
};
