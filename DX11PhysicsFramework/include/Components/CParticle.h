#pragma once
#include<Components/CPhysics.h>

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
