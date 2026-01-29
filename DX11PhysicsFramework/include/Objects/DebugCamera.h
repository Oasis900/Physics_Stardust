#pragma once
#define OBJ_CAM_DEBUGCAMERA_H
#include <Objects/BaseCamera.h>
#include <windows.h>

struct MotionData
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 right;
    DirectX::XMFLOAT3 up;
    DirectX::XMFLOAT3 look;
};

class DebugCamera : public BaseCamera
{
    MotionData* motion_ = nullptr;
    //--------------------------------------------------//
    float speed_ = 0.005f;
    float rotation_ = speed_/8.0f;
    //--------------------------------------------------//
    DirectX::XMVECTOR pos_;
    DirectX::XMVECTOR look_;
    DirectX::XMVECTOR right_;
    DirectX::XMVECTOR up_;
public:
    DebugCamera();
    //--------------------------------------------------//
    void Walk(const float& velocity);
    void Strafe(const float& velocity);
    void Elevation(const float& velocity);
    //--------------------------------------------------//
    void Yaw(const float& rotation);
    void Pitch(const float& rotation);
    //--------------------------------------------------//
    DirectX::XMFLOAT4X4 SetView() final;
    void Update(const float& dt) override;
    //--------------------------------------------------//
    ~DebugCamera() override;
};
