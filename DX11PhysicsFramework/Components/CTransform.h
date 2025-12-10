#pragma once
#ifndef COMP_TRANSFORM_HPP
#define COMP_TRANSFORM_HPP
#include "../Vec3MathLibrary.h"

// TODO (Transform Component) : Extract remaining variables and logic from game object 

class CTransform
{
    Vector3 position_;
    
public:
    void SetPosition(const Vector3& position);
    void SetPosition(const float& x, const float& y, const float& z);
    Vector3 GetPosition() const {return position_;}

    void Update(const float& dt);
};
#endif