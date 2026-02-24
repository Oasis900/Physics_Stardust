#pragma once
#define OBJ_CAM_DEBUGCAMERA_H
#include <Objects/BaseCamera.h>

struct MotionData
{
    DirectX::XMFLOAT3 position = DirectX::XMFLOAT3();
    DirectX::XMFLOAT3 right = DirectX::XMFLOAT3();
    DirectX::XMFLOAT3 up = DirectX::XMFLOAT3();
    DirectX::XMFLOAT3 look = DirectX::XMFLOAT3();
};

class DebugCamera : public BaseCamera
{
    MotionData* motion_ = nullptr;
    //--------------------------------------------------//
    DirectX::XMVECTOR pos_ = DirectX::XMVECTOR();
    DirectX::XMVECTOR look_ = DirectX::XMVECTOR();
    DirectX::XMVECTOR right_ = DirectX::XMVECTOR();
    DirectX::XMVECTOR up_ = DirectX::XMVECTOR();
public:
    DebugCamera();
    //--------------------------------------------------//
    DebugCamera(const DebugCamera& other) = delete;
    DebugCamera& operator=(const DebugCamera&) = delete;
    DebugCamera(DebugCamera&&) = delete;
    DebugCamera& operator=(const DebugCamera&&) = delete;
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
