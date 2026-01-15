#pragma once
#include <Physics/Motion.h>
#include <Interface/ICollidable.h>

// TODO (CPhysics) [12/01/26] : Review for implementation of collision detection

class CPhysics : public IUpdateable
{
    Motion* motion_ = nullptr;
    Gravity* gravity_ = nullptr;
    ICollidable::Collider* collider_ = nullptr;
    
public:
    CPhysics(CTransform* transform, const float& mass);
    //--------------------------------------------------//
    CPhysics(const CPhysics& other) = delete;
    CPhysics& operator=(const CPhysics&) = delete;
    CPhysics(CPhysics&&) = delete;
    CPhysics& operator=(const CPhysics&&) = delete;
    //--------------------------------------------------//
    Motion* GetMotion() const { return motion_;}
    //--------------------------------------------------//
    Gravity* GetGravity() const { return gravity_;}
    void ToggleGravity() const {gravity_->ToggleGravity();}
    //--------------------------------------------------//
    bool IsCollidable() const {return collider_ != nullptr;}
    ICollidable::Collider* GetCollider() const { return collider_;}
    //--------------------------------------------------//
    //void ActivateModule(); - For later
    //--------------------------------------------------//
    void Update(const float& dt) override;
    //--------------------------------------------------//
    ~CPhysics();
};
