#pragma once
#include<Components/CPhysics.h>

// TODO (Particle Component) [12/01/26] : Complete implementation, donut will act as particle for now

class CParticle : public CPhysics
{
public:
    CParticle(CTransform* transform, const float& mass) : CPhysics(transform) {}
    void Update(const float& dt) final;
};
