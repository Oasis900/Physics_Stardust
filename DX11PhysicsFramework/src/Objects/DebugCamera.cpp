#include <Objects/DebugCamera.h>
#include <Structures/Structures.h>
#include <random>
using DirectX::XMFLOAT4X4;

DebugCamera::DebugCamera()
{
    using DirectX::XMVECTOR;
    using DirectX::XMVector3Normalize;
    using DirectX::XMVectorSubtract;
    using DirectX::XMVector3Cross;
    
    // -- Converting XMFLOAT3 into XMVECTOR for calculations -- //
    XMVECTOR eye = XMLoadFloat3(&data_->eye);
    XMVECTOR at = XMLoadFloat3(&data_->at);
    XMVECTOR up = XMLoadFloat3(&data_->up);
    
    motion_ = new MotionData();
    pos_ = at;
    look_ = XMVector3Normalize(XMVectorSubtract(at, eye));
    right_ = XMVector3Normalize(XMVector3Cross(up, look_));
    up_ = XMVector3Cross(look_, right_);
}

DebugCamera::~DebugCamera()
{
    delete motion_; motion_ = nullptr;
}

void DebugCamera::Walk(const float& velocity)
{
    using DirectX::XMVECTOR;
    using DirectX::XMVectorReplicate;
    using DirectX::XMVectorMultiplyAdd;

    
    XMVECTOR v = XMVectorReplicate(velocity);
    pos_ = XMVectorMultiplyAdd(v, look_, pos_);
    XMStoreFloat3(&motion_->position, XMVectorMultiplyAdd(pos_, look_, v));
}

void DebugCamera::Strafe(const float& velocity)
{
    using DirectX::XMVECTOR;
    using DirectX::XMVectorReplicate;
    using DirectX::XMVectorMultiplyAdd;
    
    XMVECTOR v = XMVectorReplicate(velocity);
    pos_ = XMVectorMultiplyAdd(v, right_, pos_);
    XMStoreFloat3(&motion_->position, XMVectorMultiplyAdd(pos_, right_, v));
}

void DebugCamera::Elevation(const float& velocity)
{
    using DirectX::XMVECTOR;
    using DirectX::XMVectorReplicate;
    using DirectX::XMVectorMultiplyAdd;
    
    XMVECTOR v = XMVectorReplicate(velocity);
    pos_ = XMVectorMultiplyAdd(v, up_, pos_);
    XMStoreFloat3(&motion_->position, XMVectorMultiplyAdd(pos_, up_, v));
}


void DebugCamera::Yaw(const float& rotation)
{
    using DirectX::XMVECTOR;
    using DirectX::XMMATRIX;
    using DirectX::XMQuaternionRotationAxis;
    using DirectX::XMMatrixRotationQuaternion;
    
    XMVECTOR q_rotation = XMQuaternionRotationAxis(up_, rotation); 
    XMMATRIX rotate = XMMatrixRotationQuaternion(q_rotation); 
    up_ = XMVector3TransformNormal(up_, rotate);
    right_ = XMVector3TransformNormal(right_, rotate);
    look_ = XMVector3TransformNormal(look_, rotate);
}

void DebugCamera::Pitch(const float& rotation)
{
    using DirectX::XMVECTOR;
    using DirectX::XMMATRIX;
    using DirectX::XMQuaternionRotationAxis;
    using DirectX::XMMatrixRotationQuaternion;
    
    XMVECTOR q_rotation = XMQuaternionRotationAxis(right_, rotation);
    XMMATRIX rotate = XMMatrixRotationQuaternion(q_rotation);
    right_ = XMVector3TransformNormal(right_, rotate);
    look_ = XMVector3TransformNormal(look_, rotate);
}

XMFLOAT4X4 DebugCamera::SetView()
{
    using DirectX::XMVECTOR;
    using DirectX::XMMATRIX;
    using DirectX::XMLoadFloat4x4;
    using DirectX::XMVector3Normalize;
    using DirectX::XMVector3Cross;
    using DirectX::XMMatrixLookToLH;
    using DirectX::XMMatrixTranspose;
    
    XMVECTOR look = XMVector3Normalize(look_);
    XMVECTOR up = XMVector3Normalize(XMVector3Cross(look_, right_));
    XMVECTOR right = XMVector3Cross(look_, up_);
    
    XMStoreFloat3(&motion_->position, pos_);
    XMStoreFloat3(&motion_->look, look);
    XMStoreFloat3(&motion_->right, right);
    XMStoreFloat3(&motion_->up, up);

    XMStoreFloat3(&data_->at, XMLoadFloat3(&motion_->position));
    XMStoreFloat4x4(&view_, XMMatrixLookToLH(XMLoadFloat3(&motion_->position), XMLoadFloat3(&motion_->look), XMLoadFloat3(&motion_->up)));
    return view_;
}

void DebugCamera::Update(const float& dt)
{
    view_ = SetView();
    ConstantBuffer::GetInstance().SetViewMatrix(XMMatrixTranspose(XMLoadFloat4x4(&view_)));
    ConstantBuffer::GetInstance().SetEyePosW(GetAt());
}
