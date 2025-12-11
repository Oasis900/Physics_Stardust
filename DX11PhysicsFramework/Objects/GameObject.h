#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "../Components/CTransform.h"
#pragma region DX Math Variables
using DirectX::XMMATRIX;
using DirectX::XMFLOAT4X4;
using DirectX::XMFLOAT4;
using DirectX::XMFLOAT3;
#pragma endregion

#pragma region DX Matrix Functions
using DirectX::XMMatrixTranslation;
using DirectX::XMMatrixRotationX;
using DirectX::XMMatrixRotationY;
using DirectX::XMMatrixRotationZ;
using DirectX::XMMatrixScaling;
#pragma endregion

using std::string;

struct Geometry
{
	ID3D11Buffer* vertex_buffer;
	ID3D11Buffer* index_buffer;
	int indices_num;

	UINT vb_stride;
	UINT vb_offset;
};

struct Material
{
	XMFLOAT4 diffuse;
	XMFLOAT4 ambient;
	XMFLOAT4 specular;
};

class GameObject
{
	// TODO (Game Object) : Extract all transform & render variables and logic to relevant components.
	
	GameObject* parent_ = nullptr;
	CTransform* transform_comp_ = nullptr;

	XMFLOAT3 rotation_;
	XMFLOAT3 scale_;

	string type_;
	XMFLOAT4X4 world_;

	Geometry geometry_;
	Material material_;

	ID3D11ShaderResourceView* texture_rv_ = nullptr;
	
public:
	GameObject(const string& type, const Geometry& geometry, const Material& material);
	~GameObject();
	
	CTransform* GetTransform() const { return transform_comp_; }

	string GetType() const { return type_; }

	void SetParent(GameObject * parent) { parent_ = parent; }
	
	void SetScale(XMFLOAT3 scale) { scale_ = scale; }
	void SetScale(float x, float y, float z) { scale_.x = x; scale_.y = y; scale_.z = z; }

	XMFLOAT3 GetScale() const { return scale_; }

	void SetRotation(XMFLOAT3 rotation) { rotation_ = rotation; }
	void SetRotation(float x, float y, float z) { rotation_.x = x; rotation_.y = y; rotation_.z = z; }

	XMFLOAT3 GetRotation() const { return rotation_; }
	
	// Rendering information
	Geometry GetGeometryData() const { return geometry_; }
	Material GetMaterial() const { return material_; }
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&world_); }

	void SetTextureRV(ID3D11ShaderResourceView * textureRV) { texture_rv_ = textureRV; }
	ID3D11ShaderResourceView* const* GetTextureRV() { return &texture_rv_; }
	bool HasTexture() const { return texture_rv_ ? true : false; }

	void Update(const float& dt);
	void Draw(ID3D11DeviceContext * pImmediateContext);
	
};

