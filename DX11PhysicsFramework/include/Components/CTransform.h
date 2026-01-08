#pragma once
#define COMP_TRANSFORM_HPP
#include <DirectXMath.h>
#include <string>
#include <Core/Vec3MathLibrary.h>

class GameObject;

class CTransform
{
    DirectX::XMFLOAT4X4 world_ = DirectX::XMFLOAT4X4();
    DirectX::XMFLOAT3 rotation_ = DirectX::XMFLOAT3();
    DirectX::XMFLOAT3 scale_ = DirectX::XMFLOAT3();
    Vector3 position_;
    std::string type_;
    GameObject* parent_ = nullptr;
public:
    CTransform(const std::string& type);
    //--------------------------------------------------//
    void SetParent(GameObject * parent) { parent_ = parent; }
    //--------------------------------------------------//
    DirectX::XMMATRIX GetWorldMatrix() const { return DirectX::XMLoadFloat4x4(&world_); }
    void SetWorldMatrix(const DirectX::XMMATRIX& world) { XMStoreFloat4x4(&world_, world); }
    //--------------------------------------------------//
    void SetPosition(const Vector3& position) {position_ += position;}
    void SetPosition(const float& x, const float& y, const float& z) {position_.x += x; position_.y += y; position_.z += z;}
    Vector3 GetPosition() const {return position_;}
    //--------------------------------------------------//
    void SetScale(DirectX::XMFLOAT3 scale) { scale_ = scale; }
    void SetScale(float x, float y, float z) { scale_.x = x; scale_.y = y; scale_.z = z; }
    DirectX::XMFLOAT3 GetScale() const { return scale_; }
    //--------------------------------------------------//
    void SetRotation(DirectX::XMFLOAT3 rotation) { rotation_ = rotation; }
    void SetRotation(float x, float y, float z) { rotation_.x = x; rotation_.y = y; rotation_.z = z; }
    DirectX::XMFLOAT3 GetRotation() const { return rotation_; }
    //--------------------------------------------------//
    void SetParentObject(GameObject* in_parent) {parent_ = in_parent;}
    //--------------------------------------------------//
    void Update(const float& dt);
    //--------------------------------------------------//
    ~CTransform();
};
