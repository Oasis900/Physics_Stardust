#include "CTransform.h"

void CTransform::SetPosition(const Vector3& position)
{
    position_ += position;
}

void CTransform::SetPosition(const float& x, const float& y, const float& z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
}

void CTransform::Update(const float& dt)
{
   
}
