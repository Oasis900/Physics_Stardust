#pragma once
#include <Physics/Motion.h>
#include <Interface/ICollidable.h>

// TODO (CPhysics) [12/01/26] : Review for implementation of collision detection

class CPhysics : public IUpdateable
{
    Gravity* gravity_ = nullptr;
    Motion* motion_ = nullptr;
    ICollidable::Collider* collider_ = nullptr;
    
public:
    CPhysics(CTransform* transform) : gravity_(new Gravity(transform)), motion_(new Motion(transform, gravity_)) {}
    //--------------------------------------------------//
    CPhysics(const CPhysics& other) = delete;
    CPhysics& operator=(const CPhysics&) = delete;
    CPhysics(CPhysics&&) = delete;
    CPhysics& operator=(const CPhysics&&) = delete;
    //--------------------------------------------------//
    Gravity* GetGravity() const { return gravity_;}
    //void ToggleGravity() const {gravity_->ToggleGravity();}
    //--------------------------------------------------//
    Motion* GetMotion() const { return motion_;}
    //--------------------------------------------------//
    void SetMass(const float& mass) const { GetGravity()->SetMass(mass); GetMotion()->SetMass(mass);}
    //--------------------------------------------------//
    bool IsCollidable() const {return collider_ != nullptr;}
    ICollidable::Collider* GetCollider() const { return collider_;}
    //--------------------------------------------------//
    //void ActivateModule(); - For later
    //--------------------------------------------------//
    void Update(const float& dt) override;
    //--------------------------------------------------//
    virtual ~CPhysics();
};
