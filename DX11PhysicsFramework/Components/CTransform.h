#pragma once
#ifndef COMP_TRANSFORM_HPP
#define COMP_TRANSFORM_HPP
#include <DirectXMath.h>
#include "../Vec3MathLibrary.h"

#pragma region DX11 Maths & Functions
class GameObject;
using DirectX::XMMATRIX;
using DirectX::XMFLOAT4X4;
using DirectX::XMFLOAT3;
using DirectX::XMStoreFloat4x4;
using DirectX::XMMatrixScaling;
using DirectX::XMMatrixRotationX;
using DirectX::XMMatrixRotationY;
using DirectX::XMMatrixRotationZ;
using DirectX::XMMatrixTranslation;
#pragma endregion

// TODO (Transform Component) : Extract remaining variables and logic from game object 

class CTransform
{
    XMFLOAT4X4 world_ = XMFLOAT4X4();
    XMFLOAT3 rotation_ = XMFLOAT3();
    XMFLOAT3 scale_ = XMFLOAT3();
    Vector3 position_;
    GameObject* parent_ = nullptr;
    //--------------------------------------------------//
    ~CTransform();
public:
    void SetParent(GameObject * parent) { parent_ = parent; }
    //--------------------------------------------------//
    XMMATRIX GetWorldMatrix() const { return DirectX::XMLoadFloat4x4(&world_); }
    void SetWorldMatrix(const XMMATRIX& world) { XMStoreFloat4x4(&world_, world); }
    //--------------------------------------------------//
    void SetPosition(const Vector3& position) {position_ += position;}
    void SetPosition(const float& x, const float& y, const float& z) {position_.x += x; position_.y += y; position_.z += z;}
    Vector3 GetPosition() const {return position_;}
    //--------------------------------------------------//
    void SetScale(XMFLOAT3 scale) { scale_ = scale; }
    void SetScale(float x, float y, float z) { scale_.x = x; scale_.y = y; scale_.z = z; }
    XMFLOAT3 GetScale() const { return scale_; }
    //--------------------------------------------------//
    void SetRotation(XMFLOAT3 rotation) { rotation_ = rotation; }
    void SetRotation(float x, float y, float z) { rotation_.x = x; rotation_.y = y; rotation_.z = z; }
    XMFLOAT3 GetRotation() const { return rotation_; }
    //--------------------------------------------------//
    void SetParentObject(GameObject* in_parent) {parent_ = in_parent;}
    //--------------------------------------------------//
    void Update(const float& dt);
};
#endif