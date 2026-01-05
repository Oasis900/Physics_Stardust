#pragma once
#include "../Physics/Motion.h"

class CPhysics : public IUpdateable
{
    Motion* motion_ = nullptr;
    
public:
    CPhysics(CTransform* transform);
    //--------------------------------------------------//
    //void SetTransform(CTransform* transform) {transform_ = transform;};
    Motion* GetMotion() const { return motion_; }
    //--------------------------------------------------//
    //void ActivateModule();
    //--------------------------------------------------//
    void Update(const float& dt) final;
    //--------------------------------------------------//
    ~CPhysics();
    
};
