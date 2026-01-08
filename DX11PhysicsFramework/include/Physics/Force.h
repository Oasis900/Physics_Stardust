#pragma once
#include <Components/CTransform.h>

class Force
{
protected:
    CTransform* transform_ = nullptr;
    Vector3 net_force_;
    float mass_ = 0.0f;
    
public:
    Force(CTransform* transform, const float& mass);
    //--------------------------------------------------//
    void AddForce(const Vector3& force) {net_force_ += force;}
    //--------------------------------------------------//
    virtual ~Force();
};

inline Force::Force(CTransform* transform, const float& mass)
{
    mass_ = mass;
    transform_ = transform; 
}

inline Force::~Force()
{
    transform_ = nullptr;
}
