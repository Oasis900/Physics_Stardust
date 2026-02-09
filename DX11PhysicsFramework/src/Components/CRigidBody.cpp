#include <Components/CRigidBody.h>
#include <Objects/GameObject.h>
#include <Core/Debug.h>

void CRigidBody::Update(const float& dt)
{
    if (GetCollider()->CollidesWith(*GetGameObject()->GetPhysics()->GetCollider()))
    {
        Debug::DebugPrintF("Objects have collided");
    }
    
    GetMotion()->Update(dt);
}

CRigidBody::~CRigidBody()
{
    //if (collider_) {delete collider_; collider_ = nullptr;}
}
