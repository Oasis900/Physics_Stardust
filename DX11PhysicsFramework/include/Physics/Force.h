#pragma once
#include <Components/CTransform.h>

class Force
{
    CTransform* transform_ = nullptr;
    Vector3 net_force_ = Vector3(0.0f, 0.0f, 0.0f);
    float mass_ = 0.0f;
    
protected:
    CTransform* GetTransform() const {return transform_;}
    //--------------------------------------------------//
    Vector3 GetNetForce() const {return net_force_;}
    void SetNetForce(const Vector3& other) {net_force_ = other;}
    
public:
    explicit Force(CTransform* transform) : transform_(transform) {}
    //--------------------------------------------------//
    Force(const Force& other) = delete;
    Force& operator=(const Force&) = delete;
    Force(Force&&) = delete;
    Force& operator=(const Force&&) = delete;
    //--------------------------------------------------//
    float GetMass() const {return mass_;}
    void SetMass(const float& mass) {mass_ = mass;}
    float GetInverseMass() const {return 1/mass_;}
    //--------------------------------------------------//
    void AddForce(const Vector3& force) {net_force_ += force;}
    //--------------------------------------------------//
    virtual ~Force();
};

inline Force::~Force()
{
    transform_ = nullptr;
}
