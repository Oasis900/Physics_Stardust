#include "CTransform.h"

#include "../Objects/GameObject.h"

CTransform::~CTransform()
{
    if (parent_) parent_ = nullptr;
}

void CTransform::Update(const float& dt)
{
    XMMATRIX scale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
    XMMATRIX rotation = XMMatrixRotationX(rotation_.x) * XMMatrixRotationY(rotation_.y) * XMMatrixRotationZ(rotation_.z);
    XMMATRIX translation = XMMatrixTranslation(position_.x, position_.y, position_.z);

    XMStoreFloat4x4(&world_, scale * rotation * translation);

    if (parent_ != nullptr)
    {
        XMStoreFloat4x4(&world_, this->GetWorldMatrix() * parent_->GetTransform()->GetWorldMatrix());
    }
}
