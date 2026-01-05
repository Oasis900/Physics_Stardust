#pragma once
#include "CPhysics.h"

class CParticle : public CPhysics
{
public:
    CParticle(CTransform* transform, const float& mass) : CPhysics(transform, mass) {}
    void Update(const float& dt) final;
};
