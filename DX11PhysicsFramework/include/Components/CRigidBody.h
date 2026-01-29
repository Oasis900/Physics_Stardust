#pragma once
#include <Components/CPhysics.h>

// TODO (CRigidBody) [12/01/26] : Complete implementation of component for Collision detection to be functional

class CRigidBody : public CPhysics
{
public:
    CRigidBody(CTransform* transform) : CPhysics(transform) {}
    ~CRigidBody() override;
};
