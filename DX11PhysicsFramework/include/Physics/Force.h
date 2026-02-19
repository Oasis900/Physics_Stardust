#pragma once
#include <Components/CTransform.h>
#include <Structures/Structures.h>

class Force
{
    CTransform* transform_ = nullptr;
    Vector3 net_force_ = Vector3(0.0f, 0.0f, 0.0f);
    float mass_ = 0.0f;
    GameObject* object_ = nullptr;
    
protected:
    CTransform* GetTransform() const {return transform_;}
    //--------------------------------------------------//
    Vector3 GetNetForce() const {return net_force_;}
    void SetNetForce(const Vector3& other) {net_force_ = other;}
    //--------------------------------------------------//
    GameObject* GetGameObject() const { return object_; }
    
public:
    explicit Force(CTransform* transform) : transform_(transform) {}
    //--------------------------------------------------//
    Force(const Force& other) = delete;
    Force& operator=(const Force&) = delete;
    Force(Force&&) = delete;
    Force& operator=(const Force&&) = delete;
    //--------------------------------------------------//
    void SetMass(const float& mass) {mass_ = mass;}
    float GetMass() const {return mass_;}
    float GetInverseMass() const {if (mass_ <= 0) {return 0;} return 1/mass_;}
    //--------------------------------------------------//
    void AddGameObject(GameObject* game_object) { object_ = game_object; }
    //--------------------------------------------------//
    void AddForce(const Vector3& force) {net_force_ += force;}
    void SubtractForce(const Vector3& force) {net_force_ -= force;}
    //--------------------------------------------------//
    virtual ~Force();
};

inline Force::~Force()
{
    transform_ = nullptr;
    object_ = nullptr;
}
