#pragma once
#include "../Physics/Motion.h"

class CPhysics : public IUpdateable
{
    Motion* motion_ = nullptr;
    
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
    //void ActivateModule(); - For later
    //--------------------------------------------------//
    void Update(const float& dt) override;
    //--------------------------------------------------//
    ~CPhysics() override;
};
