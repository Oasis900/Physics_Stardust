#include <Objects/BaseCamera.h>
#include <Structures/Structures.h>

void BaseCamera::SetLens()
{
    using DirectX::XMMATRIX;
    using DirectX::XMMatrixPerspectiveFovLH;
    using DirectX::XMConvertToRadians;
    
    // -- Matrix used for arithmetic calculations -- //
    XMMATRIX perspective = XMMatrixPerspectiveFovLH(XMConvertToRadians(fov_), aspect_, near_depth_, far_depth_);
    // -- Place matrix calculation data into suitable long term data format -- //
    XMStoreFloat4x4(&projection_, perspective);
    // --- 64 bits - 16 bytes --- //
    ConstantBuffer::GetInstance().SetProjectionMatrix(XMMatrixTranspose(XMLoadFloat4x4(&projection_)));
}

BaseCamera::BaseCamera()
{
    using DirectX::XMFLOAT3;
    
    SetLens();
    //--------------------------------------------------//
    data_ = new CameraData();
    data_->eye = XMFLOAT3(0,0,-20);
    data_->at = XMFLOAT3(0.0f, 0.0f, -6.0f);
    data_->up = XMFLOAT3(0.0f, 1.0f, 0.0f);
}

BaseCamera::~BaseCamera()
{
    if (data_) {delete data_; data_ = nullptr;}
}

