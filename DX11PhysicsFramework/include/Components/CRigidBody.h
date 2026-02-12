#pragma once
#include <Components/CPhysics.h>

#include "Observer/ISubject.h"

// TODO (CRigidBody) [12/01/26] : Complete implementation of component for Collision detection to be functional

constexpr float restitution = 1E-6; 

class CRigidBody : public CPhysics
{
    
public:
    CRigidBody(CTransform* transform) : CPhysics(transform) {}
    //--------------------------------------------------//
    CRigidBody(const CRigidBody& other) = delete;
    CRigidBody& operator=(const CRigidBody&) = delete;
    CRigidBody(CRigidBody&&) = delete;
    CRigidBody& operator=(const CRigidBody&&) = delete;
    //--------------------------------------------------//
    void ApplyImpulse(const Vector3& impulse, const float& dt); 
    //--------------------------------------------------//
    void Update(const float& dt) override;
    //--------------------------------------------------//
    ~CRigidBody() override = default;
};
