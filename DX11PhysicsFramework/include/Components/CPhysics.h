#pragma once
#include <Physics/Motion.h>
#include <Physics/Gravity.h>
#include <Physics/Drag.h>
#include <Core/Collidable.h>

class CPhysics : public IUpdateable
{
    Gravity* gravity_ = nullptr;
    Drag* drag_ = nullptr;
    Motion* motion_ = nullptr;
    CTransform* transform_ = nullptr;
    Colliders::Collider* collider_ = nullptr;
    GameObject* object_ = nullptr;
    float mass_ = 0.0f;

protected:
    CTransform* GetTransform() const { return transform_; }
    
public:
    CPhysics(CTransform* transform) : gravity_(new Gravity(transform)), drag_(new Drag(transform, gravity_)), motion_(new Motion(transform, gravity_, drag_)), transform_(transform) {}
    //--------------------------------------------------//
    CPhysics(const CPhysics& other) = delete;
    CPhysics& operator=(const CPhysics&) = delete;
    CPhysics(CPhysics&&) = delete;
    CPhysics& operator=(const CPhysics&&) = delete;
    //--------------------------------------------------//
    Motion* GetMotion() const { return motion_;}
    //--------------------------------------------------//
    void SetMass(const float& mass) {mass_ = mass; gravity_->SetMass(mass_); motion_->SetMass(mass_);}
    float GetMass() const {return mass_;}
    float GetInverseMass() const {if (mass_ <= 0) {return 0;} return 1/mass_;}
    //--------------------------------------------------//
    void SetCollider(Colliders::Collider* collider) {collider_ = collider;} 
    bool IsCollidable() const {return collider_ != nullptr;}
    Colliders::Collider* GetCollider() const { return collider_;}
    //--------------------------------------------------//
    void AddGameObject(GameObject* game_object) { object_ = game_object; gravity_->AddGameObject(game_object); motion_->AddGameObject(game_object); drag_->AddGameObject(game_object);}
    GameObject* GetGameObject() const { return object_; }
    //--------------------------------------------------//
    void Update(const float& dt) override = 0;
    //--------------------------------------------------//
    ~CPhysics() override;
};
