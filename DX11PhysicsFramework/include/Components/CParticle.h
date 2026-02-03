#pragma once
#include<Components/CPhysics.h>

// TODO (Particle Component) [12/01/26] : Complete implementation, donut will act as particle for now

class CParticle : public CPhysics
{
public:
    explicit CParticle(CTransform* transform) : CPhysics(transform) {}
    //--------------------------------------------------//
    CParticle(const CParticle& other) = delete;
    CParticle& operator=(const CParticle&) = delete;
    CParticle(CParticle&&) = delete;
    CParticle& operator=(const CParticle&&) = delete;
    //--------------------------------------------------//
    void Update(const float& dt) final;
};
