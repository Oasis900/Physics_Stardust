#include "CParticle.h"

void CParticle::Update(const float& dt)
{
    static float time_alive = 0.0f; // For particles life time

    CPhysics::Update(dt);
}
