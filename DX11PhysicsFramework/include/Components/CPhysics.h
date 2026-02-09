#pragma once
#include <Physics/Motion.h>
#include <Core/Collidable.h>

// TODO (CPhysics) [12/01/26] : Review for implementation of collision detection

class CPhysics : public IUpdateable
{
    Gravity* gravity_ = nullptr;
    Motion* motion_ = nullptr;
    CTransform* transform_ = nullptr;
    Colliders::Collider* collider_ = nullptr;
    GameObject* object_ = nullptr;
    float mass_ = 0.0f;

protected:
    CTransform* GetTransform() const { return transform_; }
    //--------------------------------------------------//
    Gravity* GetGravity() const { return gravity_;}
    
public:
    CPhysics(CTransform* transform) : gravity_(new Gravity(transform)), motion_(new Motion(transform, gravity_)), transform_(transform) {}
    //--------------------------------------------------//
    CPhysics(const CPhysics& other) = delete;
    CPhysics& operator=(const CPhysics&) = delete;
    CPhysics(CPhysics&&) = delete;
    CPhysics& operator=(const CPhysics&&) = delete;
    //--------------------------------------------------//
    Motion* GetMotion() const { return motion_;}
    //--------------------------------------------------//
    
    //--------------------------------------------------//
    void SetMass(const float& mass) {mass_ = mass; GetGravity()->SetMass(mass_); GetMotion()->SetMass(mass_);}
    float GetMass() const {return mass_;}
    float GetInverseMass() const {if (mass_ <= 0) {return 0;} return 1/mass_;}
    //--------------------------------------------------//
    void SetCollider(Colliders::Collider* collider) {collider_ = collider;} 
    bool IsCollidable() const {return collider_ != nullptr;}
    Colliders::Collider* GetCollider() const { return collider_;}
    //--------------------------------------------------//
    void AddGameObject(GameObject* game_object) { object_ = game_object; gravity_->AddGameObject(game_object);}
    GameObject* GetGameObject() const { return object_; }
    //--------------------------------------------------//
    //void ActivateModule(); - For later
    //--------------------------------------------------//
    void Update(const float& dt) override = 0;
    //--------------------------------------------------//
    ~CPhysics() override;
};
