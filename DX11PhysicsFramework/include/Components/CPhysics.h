#pragma once
#include "../Physics/Motion.h"

class CPhysics : public IUpdateable
{
protected:
    Motion* motion_ = nullptr;
    
public:
    CPhysics(CTransform* transform, const float& mass);
    //--------------------------------------------------//
    Motion* GetMotion() const { return motion_;}
    //--------------------------------------------------//
    //void ActivateModule(); - For later
    //--------------------------------------------------//
    void Update(const float& dt) override;
    //--------------------------------------------------//
    ~CPhysics();
    
};
